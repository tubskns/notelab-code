import requests
import json


def get_data(url):
    req = requests.get(url)
    print("HTTP - [" + url + "] response code: ", req.status_code)
    if req.status_code is 200:
        res_json = json.loads(req.content.decode('utf8'))
        return res_json
    else:
        return None


if __name__ == "__main__":
    # parameters
    url = "http://192.168.1.7:9200/index/"
    data = get_data(url)
    print("Data retrived from ElasticSearch: " + json.dumps(data))
