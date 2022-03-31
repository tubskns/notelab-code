import requests
import json
import time


def perform_request(url, method, payload=None):
    try:
        res = requests.Response()
        if method == "GET":
            res = requests.get(url)
        if method == "POST":
            res = requests.post(
                url,
                data=json.dumps(payload),
                headers={"content-type": "application/json"},
            )
        if method == "PUT":
            res = requests.put(
                url,
                data=json.dumps(payload),
                headers={"content-type": "application/json"},
            )
        if method == "DELETE":
            res = requests.delete(url)
        res_content = None
        if res.content is not None:
            res_content = json.loads(res.content.decode("utf8"))
        print(
            "HTTP client - " + method + " - [" + url + "] response code: ",
            res.status_code,
            ", content: " + json.dumps(res_content, indent=4, sort_keys=True),
        )
        return res_content
    except:
        print("HTTP client - " + method + " - Connection error!")


if __name__ == "__main__":
    root_url = "http://134.169.115.45:9200/"
    index_es = "testindex"
    perform_request(
        url=root_url + index_es + "/test_sensor/1",
        method="POST",
        payload={"tester": "worksation", "sensor_data": 23},
    )
    perform_request(
        url=root_url + index_es + "/test_sensor/1",
        method="PUT",
        payload={"tester": "worksation", "sensor_data": 15},
    )
    time.sleep(1)
    perform_request(url=root_url + index_es + "/" + "_search", method="GET")
    perform_request(url=root_url + index_es, method="DELETE")
