#include<iostream>
#include<string>
#include<curl/curl.h>
#include<json/json.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, const char *argv[]) {
	CURL *curl;//указатель на структуру
	CURLcode res;;
	std::string buffer;
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/getFriends?uid=31733100");
		//установить опцию(стр,)
		/* example.com is redirected, so we tell libcurl to follow redirection */
		//редирект- направление на другой сайт
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//задание поведение при ответе на редирект.1l- long
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		//задание поведение при ответе на редирект.1l- long
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//задание поведение при ответе на редирект.1l- long

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);//исполнить
		/* Check for errors */ 
		if(res != CURLE_OK)//curle- коды ошибок
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
		//std::cout << buffer << std::endl;
		json_object *jobj = json_tokener_parse(buffer.c_str());
		json_object *resp;
		resp = json_object_object_get(jobj, "response");
		std::string str(json_object_to_json_string(jobj));
		std::string rstr(json_object_to_json_string(resp));
		json_object *jval = json_object_array_get_idx(resp,4);
		std::string sval(json_object_to_json_string(jval));
		std::cout << str << std::endl;
		std::cout << rstr << std::endl;
		std::cout << sval << std::endl;
	}
	return 0;
}
