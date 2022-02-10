import requests
import json


def get_data(url):
    res = requests.get(url)
    print("HTTP client - [" + url + "] response code: ", res.status_code)
    if res.status_code == 200:
        res_json = json.loads(res.content.decode('utf8'))
        return res_json
    else:
        return None


if __name__ == "__main__":
    # parameters
    url = "http://192.168.1.7:9200/test_index/_search?pretty"
    data = get_data(url)
    print("Data retrived from ElasticSearch: " + json.dumps(data))
