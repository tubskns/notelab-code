import requests, json, time

def query(url, method, payload=None):
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
            "HTTP client - " + method + " - [" + url + "] code: ",
            res.status_code,
            ", content: " + json.dumps(res_content, indent=4),
        )
        return res_content
    except:
        print("HTTP client - " + method + " - Connection error!")

if __name__ == "__main__":
    root_url = "http://192.168.1.3:9200/"
    index_es = "testindex"
    query(
        url=root_url + index_es + "/test_sensor/1",
        method="POST",
        payload={"tester": "worksation", "sensor_data": 23},
    )
    query(
        url=root_url + index_es + "/test_sensor/1",
        method="PUT",
        payload={"tester": "worksation", "sensor_data": 15},
    )
    time.sleep(1)
    query(url=root_url + index_es + "/" + "_search", method="GET")
    query(url=root_url + index_es, method="DELETE")
