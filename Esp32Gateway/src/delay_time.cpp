#include "time.h"
#include "getTime.h"

extern int hourStart, minStart, secStart;
extern int hourEnd, minEnd, secEnd;

void getPowerPerMinute(void *)
{
    int previousMinute = -1;
    while (1)
    {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Không lấy được thời gian.");
            cannot_get_time();
        }
        else
        {
            char timeString[20];
            strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);
            Serial.println(timeString);

            if (timeinfo.tm_min != previousMinute)
            {
                // Lưu trữ thời gian bắt đầu
                struct tm start_tm = {0};
                start_tm.tm_year = timeinfo.tm_year;
                start_tm.tm_mon = timeinfo.tm_mon;
                start_tm.tm_mday = timeinfo.tm_mday;
                start_tm.tm_hour = hourStart;
                start_tm.tm_min = minStart;
                start_tm.tm_sec = secStart;

                // Lưu thời gian kết thúc (hiện tại)
                struct tm end_tm = timeinfo;

                // Chuyển thành timestamp (giây từ Epoch)
                time_t start_time = mktime(&start_tm);
                time_t end_time = mktime(&end_tm);

                // Tính thời gian trễ
                long delay_seconds = difftime(end_time, start_time);

                Serial.printf("Thời gian trễ: %ld giây\n", delay_seconds);

                // Cập nhật thời gian bắt đầu/kết thúc
                hourStart = hourEnd;
                minStart = minEnd;
                secStart = secEnd;
                hourEnd = timeinfo.tm_hour;
                minEnd = timeinfo.tm_min;
                secEnd = timeinfo.tm_sec;

                // Nhận dữ liệu từ STM và xử lý JSON (như trước)
                String PowerReceive;
                for (int i = 0; i < 5; i++)
                {
                    STM_Transmit_Process("AA");
                    delay(50);
                    PowerReceive = STM_Receive_Process();
                    if (PowerReceive != "")
                        break;
                }
                previousMinute = timeinfo.tm_min;

                // Chuẩn bị JSON và gửi như trước
                char beginTime[30], endTime[30];
                snprintf(beginTime, sizeof(beginTime), "%04d-%02d-%02dT%02d:%02d:%02d",
                         timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                         hourStart, minStart, secStart);
                snprintf(endTime, sizeof(endTime), "%04d-%02d-%02dT%02d:%02d:%02d",
                         timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                         hourEnd, minEnd, secEnd);

                StaticJsonDocument<256> doc;
                doc["beginTime"] = beginTime;
                doc["endTime"] = endTime;
                doc["Data"] = PowerReceive;
                doc["delay_seconds"] = delay_seconds; // Thêm thời gian trễ vào JSON

                char payload[512];
                serializeJson(doc, payload);

                char responseTopic[70];
                snprintf(responseTopic, sizeof(responseTopic), "%s/power-average/response", macAddress.c_str());
                publishMessage(responseTopic, payload);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
