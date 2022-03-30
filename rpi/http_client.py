#from email import message
import requests
import json


# retrieve data from HTTP server
def get_data(url):
    res = requests.get(url)
    print("HTTP client - [" + url + "] response code: ", res.status_code)
    if res.status_code == 200:
        res_json = json.loads(res.content.decode('utf8'))
        return res_json
    else:
        return None
        
# post data to HTTP server
def post_data(url, payload):  
    #Content type must be included in the header
    json_header = {"content-type": "application/json"}
    query = json.dumps(payload)
    res = requests.post(url, data=query, headers=json_header)
    print("HTTP client - [" + url + "] response code: ", res.status_code)
    if res.status_code == 200:
        res_json = json.loads(res.content.decode('utf8'))
        return res_json
    else:
        return None

 # update data
def put_data(url, payload):
    json_header = {"content-type": "application/json"}
    query = json.dumps(payload)
    res = requests.put(url, data=query, headers=json_header)
    print("HTTP client - [" + url + "] response code: ", res.status_code)
    if res.status_code == 200:
        res_json = json.loads(res.content.decode('utf8'))
        return res_json
    else:
        return None

 # delete data
def delete_data(url):
    res = requests.delete(url)
    print("HTTP client - [" + url + "] response code: ", res.status_code)
    if res.status_code == 200:
        res_json = json.loads(res.content.decode('utf8'))
        return res_json
    else:
        return None




if __name__ == "__main__":
    # parameters
    index_name = "testindex"
    server_url = "http://134.169.115.45:9200/" 
    index_type = "test_sensor" #  type of data in the same index
    index_id = "1"  # document’s ID.
    payload = {"tester":"worksation", "sensor_data": 23}

    # join server url with index parameters
    post_url = server_url + index_name + '/' + index_type + '/' + index_id 
    data_to_send = post_data(post_url, payload)
    print(" Data sent with POST method: " + json.dumps(data_to_send))
    
    #modify the sensor value
    put_url = server_url + index_name + '/' + index_type + '/' + index_id 
    updated_payload = {"tester":"worksation", "sensor_data": 15}
    data_to_update = post_data(put_url, updated_payload)
    print(" Data sent with PUT method: " + json.dumps(data_to_update))


    #retrieve all data stored under index with pretty search
    get_url =  server_url + index_name + '/' + "_search?pretty" 
    data_to_retrieve = get_data(get_url)
    print(" Data retrieved with GET method: " + json.dumps(data_to_retrieve))

    #delete the data stored under index
    delete_url =  server_url + index_name + '/' 
    delete_data(delete_url)
    print(" Deleted index: " + index_name)

