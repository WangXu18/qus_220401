#include <iostream>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

int main()
{
  const char* json = "{\"name\":\"网站\",\"num\":3,\"sites\":[\"Google\",\"Runoob\",\"Taobao\"]}";

  rapidjson::Document doc;
  doc.Parse(json);

  rapidjson::Value& value = doc["name"];
  value.SetString("中国");

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
  doc.Accept(write);

  std::cout << buffer.GetString() << std::endl;
  return 0;
}
