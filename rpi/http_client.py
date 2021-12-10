import requests
import json


def get_data(url):
    headers = {"Content-type": "application/json", "Accept": "text/plain"}
    req = requests.get(url, headers=headers)
    print("Status code: ", req.status_code)
    return req.content


if __name__ == "__main__":
    # parameters
    url = "http://192.168.1.7:9200/index/"
    data = get_data(url)
    print("Data retrived from ElasticSearch: " + json.dumps(data))
