#include "httpWrapper.h"

void HTTPWrapper::testConnection()
{
  std::string endpointString = std::string(HOST) + std::string("/api");
  char *endpoint = (char *)endpointString.c_str();
  Serial.println("Testing GET and POST connection to " + String(endpoint));
  http.begin(endpoint); // HTTP

  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      Serial.println("GET successful");
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  http.begin(endpoint); // HTTP

  // start connection and send HTTP header
  httpCode = http.POST("");

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      Serial.println("POST successful");
    }
  }
  else
  {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

int HTTPWrapper::postMeasurements(float temp, float humd, float ph, bool light)
{
  http.begin(HOST + String("/api/reading"));
  http.addHeader("Content-Type", "application/json");
  cJSON *root = cJSON_CreateObject();

  std::string light_string;
  if (light)
  {
    light_string = "true";
  }
  else
  {
    light_string = "false";
  }

  // Add data to the JSON object
  cJSON_AddNumberToObject(root, "temp", temp);
  cJSON_AddNumberToObject(root, "humd", humd);
  cJSON_AddNumberToObject(root, "ph", ph);
  cJSON_AddStringToObject(root, "light", light_string.c_str());

  char *postData = cJSON_Print(root);

  int httpResponseCode = http.POST(postData);

  cJSON_Delete(root);
  free(postData);
  http.end();

  if (httpResponseCode <= 0)
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  return httpResponseCode;
}

State HTTPWrapper::getState()
{
  http.begin(HOST + String("/api/state"));

  int httpResponseCode = http.GET();

  if (httpResponseCode != HTTP_CODE_OK)
  {
    Serial.print("Error on sending GET: ");
    Serial.println(t_http_codes(httpResponseCode));
    http.end();
    return State();
  }
  cJSON *root = cJSON_Parse(http.getString().c_str());

  State state(cJSON_GetStringValue(cJSON_GetObjectItem(root, "name")), cJSON_IsTrue(cJSON_GetObjectItem(root, "light_state")), cJSON_GetNumberValue(cJSON_GetObjectItem(root, "ph_poll_interval")), cJSON_GetNumberValue(cJSON_GetObjectItem(root, "dht_poll_interval")));
  cJSON_Delete(root);
  http.end();
  return state;
}

void HTTPWrapper::postMemory()
{
  http.begin(HOST + String("/api/memory"));
  http.addHeader("Content-Type", "application/json");
  cJSON *root = cJSON_CreateObject();

  cJSON_AddNumberToObject(root, "free_heap", ESP.getFreeHeap());
  cJSON_AddNumberToObject(root, "min_free_heap", ESP.getMinFreeHeap());
  cJSON_AddNumberToObject(root, "max_alloc_heap", ESP.getMaxAllocHeap());

  char *postData = cJSON_Print(root);

  int httpResponseCode = http.POST(postData);

  cJSON_Delete(root);
  free(postData);

  if (httpResponseCode <= 0)
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}