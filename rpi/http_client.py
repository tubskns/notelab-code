import requests, json, time
import logging


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
        if res.content is not None:
            logging.debug(
                "HTTP - [" + method + "][" + str(res.status_code) + "][" + url + "]"
            )
            return json.loads(res.content.decode("utf8"))
    except:
        logging.error("HTTP - " + method + " - Connection error!")


if __name__ == "__main__":
    logging.basicConfig(
        format="%(asctime)s | %(name)s | %(levelname)s | %(message)s",
        level=logging.DEBUG,
    )
    root_url = "http://SERVER_IP:9200"
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
