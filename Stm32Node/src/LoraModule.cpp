#include "LoraModule.h"
String gatewayId;
int addrGatewayId = 4;
bool LoraSender = false;
uint32_t waitDuration = 30 * 1000000; // Thời gian chờ mặc định là 30 giây
void LoraSetup()
{
    pinMode(SPI1_NSS, OUTPUT);
    pinMode(SPI1_RESET, OUTPUT);
    digitalWrite(SPI1_RESET, HIGH);
    pinMode(PB10, OUTPUT); // Cấu hình chân PB10 làm đầu ra
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6))
    {
        Serial.println("LoRa init failed. Check your connections.");
        delay(5000);
    }
    Serial.println("LoRa init succeeded.");
    LoRa.receive();
}

void sendSensorData(String gatewayId, int penCode, int nodeId, float t, float h, float nh3, float h2s)
{
    beginSend();
    bool ackReceived = false;
    int count = 0;
    while (!ackReceived && count <= 3)
    {
        LoRa.beginPacket();
        LoRa.print("gatewayId:");
        LoRa.print(gatewayId);
        LoRa.print("; penCode:");
        LoRa.print(penCode, DEC);
        LoRa.print("; nodeId:");
        LoRa.print(nodeId, DEC);
        LoRa.print("; Temp:");
        LoRa.print(t);
        LoRa.print("; Hum:");
        LoRa.print(h);
        LoRa.print("; NH3:");
        LoRa.print(nh3);
        LoRa.print("; H2S:");
        LoRa.print(h2s);
        LoRa.endPacket();
        unsigned long startTime = millis();
        while (millis() - startTime < 5000)
        {
            int packetSize = LoRa.parsePacket();
            if (packetSize)
            {
                String response = LoRa.readString(); // Đọc gói tin phản hồi
                if (response.startsWith("OK/"))
                {
                    // Giải mã phản hồi để kiểm tra penCode và nodeId
                    String receivedMac = response.substring(3, response.indexOf('/', 3));
                    int receivedPenCode = response.substring(response.indexOf('/', 3) + 1, response.lastIndexOf('/')).toInt();
                    int receivedNodeId = response.substring(response.lastIndexOf('/') + 1).toInt();

                    if (receivedMac == gatewayId && receivedPenCode == penCode && receivedNodeId == nodeId)
                    {
                        digitalWrite(PB10, HIGH);
                        delay(200);
                        digitalWrite(PB10, LOW);
                        ackReceived = true;
                        break;
                    }
                }
            }
        }
    count++;
    }
    endSend();
}
bool receiveLoraData(String &receivedData)
{
    if (!LoraSender)
    {
        int packetSize = LoRa.parsePacket();
        if (packetSize)
        {
            receivedData = "";
            while (LoRa.available())
            {
                receivedData += (char)LoRa.read();
            }
            return true;
        }
        return false;
    }
    else
        return false;
}

void processReceivedData(String &data)
{
    if (data.startsWith("time/"))
{
    // Tách các phần của gói tin (time/macAddress/penCode/NodeId/timeChange)
    int firstSlash = data.indexOf('/');
    int secondSlash = data.indexOf('/', firstSlash + 1);
    int thirdSlash = data.indexOf('/', secondSlash + 1);
    int fourthSlash = data.indexOf('/', thirdSlash + 1);

    String receivedMacAddress = data.substring(firstSlash + 1, secondSlash);
    String receivedpenCode = data.substring(secondSlash + 1, thirdSlash);
    String receivednodeId = data.substring(thirdSlash + 1, fourthSlash);
    String timeValue = data.substring(fourthSlash + 1); // Giá trị sau "/" thứ 4 là timeChange

    int timeChange = timeValue.toInt(); // Chuyển đổi thành số nguyên (thời gian thay đổi)

    // Kiểm tra nếu địa chỉ MAC nhận được trùng với gatewayId
    if (receivedMacAddress == gatewayId && penCode == receivedpenCode.toInt() && nodeId == receivednodeId.toInt())
    {
        if (timeChange > 0)
        {
            beginSend();

            int maxAttempts = 10;
            bool ackSent = false;
            for (int attempt = 0; attempt < maxAttempts; attempt++)
            {
                int rssi = LoRa.packetRssi();
                if (rssi < -90) // RSSI thấp nghĩa là kênh không bận
                {
                    LoRa.beginPacket();
                    LoRa.print("BCK,");
                    LoRa.print(gatewayId); // Gửi lại macAddress
                    LoRa.print(",");
                    LoRa.print(penCode); // Gửi lại penCode
                    LoRa.print(",");
                    LoRa.print(nodeId); // Gửi lại nodeId
                    LoRa.endPacket();
                    ackSent = true;
                    break;
                }
                else
                {
                    delay(random(500, 1500)); // Retry khi kênh bận
                }
            }

            endSend();

            if (ackSent)
            {
                EEPROMLib::writeInt(32, timeChange); // Ghi thời gian thay đổi vào EEPROM

                // Chuyển đổi thời gian thành micro giây và thực hiện các hành động cần thiết
                waitDuration = timeChange * 1000; // Chuyển đổi thành micro giây

                for (int i = 0; i < 4; i++)
                {
                    changeTimeBuzzer(); // Gọi hàm báo hiệu thành công thay đổi thời gian
                }
            }
            else
            {
                Serial.println("Failed to send ACK");
            }
        }
        else
        {
            Serial.println("Invalid timeChange value received");
        }
    }
    else
    {
        Serial.println("Received MAC address does not match Gateway ID");
    }
}
    // Kiểm tra gói dữ liệu "rsID:"
    else if (data.startsWith("rsID:"))
    {
        // Thực hiện tín hiệu LED khi nhận được gói tin
        digitalWrite(PB10, HIGH);
        delay(200);
        digitalWrite(PB10, LOW);
        readAllSwitches();
        String values = data.substring(5); // Lấy phần sau "rsID:"

        // Tìm vị trí dấu phẩy đầu tiên
        int commaIndex1 = values.indexOf(',');
        // Tìm vị trí dấu phẩy thứ hai bắt đầu từ sau dấu phẩy đầu tiên
        int commaIndex2 = values.indexOf(',', commaIndex1 + 1);

        if (commaIndex1 > 0 && commaIndex2 > commaIndex1)
        {
            // Tách giá trị trước và sau dấu phẩy
            String penCodeString = values.substring(0, commaIndex1);
            String nodeIdString = values.substring(commaIndex1 + 1, commaIndex2);
            String newGatewayId = values.substring(commaIndex2 + 1); // Phần còn lại là newGatewayId

            // Chuyển đổi chuỗi sang số nguyên
            int penCodeReceive = penCodeString.toInt();
            int nodeIdReceive = nodeIdString.toInt();
            
            // Kiểm tra và so sánh với giá trị đã cài đặt
            if (penCodeReceive == penCode && nodeIdReceive == nodeId && !digitalRead(DIPSW1))
            {
                gatewayId = newGatewayId;
                
                EEPROMLib::writeString(0,gatewayId);
                
                beginSend();
                int maxAttempts = 5;
                for (int attempt = 0; attempt < maxAttempts; attempt++)
                {
                    int rssi = LoRa.packetRssi();
                    if (rssi < -90)
                    {
                        LoRa.beginPacket();
                        // Gửi dữ liệu theo định dạng yêu cầu: "ACK,newGatewayId,penCodeReceive,nodeIdReceive"
                        LoRa.print("ACK,");
                        LoRa.print(gatewayId); // Gửi newGatewayId
                        LoRa.print(",");
                        LoRa.print(penCodeReceive); // Gửi penCodeReceive
                        LoRa.print(",");
                        LoRa.print(nodeIdReceive); // Gửi nodeIdReceive
                        LoRa.endPacket();
                        break;
                    }
                    else
                    {
                        delay(random(100, 500)); // Retry khi kênh bận
                    }
                }
                endSend();
                resetGatewayIDBuzz();
            }
        }
    }
}

void resetLoRaModule()
{
    pinMode(SPI1_RESET, OUTPUT);
    // Đặt chân RESET xuống mức LOW để reset module
    digitalWrite(SPI1_RESET, LOW);
    delay(10); // Giữ mức thấp trong 10ms
    // Đưa chân RESET trở lại mức HIGH
    digitalWrite(SPI1_RESET, HIGH);
    delay(10); // Chờ module khởi động lại
}

void beginSend(void)
{
    LoraSender = true;
    resetLoRaModule();
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6))
    {
        // buzzer_fail_Lora();
    }
    LoRa.idle();
}

void endSend(void)
{
    resetLoRaModule();
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6))
    {
    }
    LoRa.receive();
    LoraSender = false;
}
