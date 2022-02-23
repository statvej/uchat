#include <stdio.h> 
#include <stdlib.h> 
#include "../libs/cJSON/cJSON.h"

int main()
{
  cJSON *root = cJSON_CreateObject();
  cJSON_AddStringToObject(root, "squadName", "Super hero squad");
  cJSON_AddStringToObject(root, "homeTown", "sugoma");
  cJSON_AddNumberToObject(root, "formed", 2016);
  cJSON_AddStringToObject(root, "secretBase", "cum");
  cJSON_AddStringToObject(root, "active", "true");

  char *json = NULL;
  json = cJSON_Print(root);
  printf("%s", json);
  cJSON_Delete(root);
  free(json);
  //cJSON_Delete(root);

  return 0;
}
