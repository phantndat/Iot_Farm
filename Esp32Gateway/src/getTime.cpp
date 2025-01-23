#include "getTime.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600; // Múi giờ UTC+7 (cho Việt Nam)
const int daylightOffset_sec = 0;    // Không có giờ mùa hè
int hourStart, minStart, secStart;
int hourEnd, minEnd, secEnd;
void getTime_Setup()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void getPowerPerMinute(void *)
{
    String PowerReceive;
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
                // Thời gian bị delay (tính toán trong chu kỳ trước)
                const int delayInSeconds = 1 + 5 * 50 / 1000; // 1 giây (vTaskDelay) + 5 lần delay(50ms)

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

                // Chuyển thành timestamp
                time_t start_time = mktime(&start_tm);
                time_t end_time = mktime(&end_tm);

                // Trừ thời gian delay
                start_time -= delayInSeconds; // Điều chỉnh thời gian bắt đầu
                end_time -= delayInSeconds;   // Điều chỉnh thời gian kết thúc

                // Chuyển lại timestamp về struct tm
                struct tm *adjusted_start_tm = localtime(&start_time);
                struct tm *adjusted_end_tm = localtime(&end_time);

                // Chuẩn bị chuỗi thời gian
                char beginTime[30], endTime[30];
                snprintf(beginTime, sizeof(beginTime), "%04d-%02d-%02dT%02d:%02d:%02d",
                         adjusted_start_tm->tm_year + 1900, adjusted_start_tm->tm_mon + 1, adjusted_start_tm->tm_mday,
                         adjusted_start_tm->tm_hour, adjusted_start_tm->tm_min, adjusted_start_tm->tm_sec);
                snprintf(endTime, sizeof(endTime), "%04d-%02d-%02dT%02d:%02d:%02d",
                         adjusted_end_tm->tm_year + 1900, adjusted_end_tm->tm_mon + 1, adjusted_end_tm->tm_mday,
                         adjusted_end_tm->tm_hour, adjusted_end_tm->tm_min, adjusted_end_tm->tm_sec);

                // Tạo JSON và gửi dữ liệu
                StaticJsonDocument<256> doc;
                doc["beginTime"] = beginTime;
                doc["endTime"] = endTime;
                doc["Data"] = PowerReceive;

                char payload[512];
                serializeJson(doc, payload);

                char responseTopic[70];
                snprintf(responseTopic, sizeof(responseTopic), "%s/power-average/response", macAddress.c_str());
                publishMessage(responseTopic, payload);

                // Cập nhật biến thời gian cho lần lặp sau
                hourStart = hourEnd;
                minStart = minEnd;
                secStart = secEnd;
                hourEnd = adjusted_end_tm->tm_hour;
                minEnd = adjusted_end_tm->tm_min;
                secEnd = adjusted_end_tm->tm_sec;

                previousMinute = timeinfo.tm_min;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
