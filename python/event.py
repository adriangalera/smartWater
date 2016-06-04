import falcon
import json
from eventModel import EventModel
from bson.objectid import ObjectId
import datetime

class Event(object):

    def on_get(self, req, resp):
        now = datetime.datetime.now();
        querydate = now - datetime.timedelta(days=1)
        if req.params.get('date', None):
            
            arrdate = req.params['date'].split("-");
            year = int(arrdate[0]);
            month = int(arrdate[1]);
            day = int(arrdate[2].split(" ")[0]);
            hour = int(arrdate[2].split(" ")[1].split(":")[0]);
            minute = int(arrdate[2].split(" ")[1].split(":")[1]);
            second = int(arrdate[2].split(" ")[1].split(":")[2]);
            querydate = datetime.datetime(year,month,day,hour,minute,second);
        printMsg("Request ::: "+querydate) ;
        dummy_id = ObjectId.from_datetime(querydate)
        result = EventModel.objects(id__gt = dummy_id)[:100];
       	json_string = json.dumps([r.obj_dict() for r in result])
       	resp.body = json_string;
       	resp.status = falcon.HTTP_200

    def on_post(self, req, resp):
        resp.body = '{"message": "Hello world POST!"}'
        body = req.stream.read();
        if not body:
        	raise falcon.HTTPBadRequest('Empty request body' , 'Need valid JSON');
        content = json.loads(body.decode('UTF-8'))
        printMsg(content);
        eventModel = EventModel();
        eventModel.from_json(content);
        eventModel.save();
        resp.status = falcon.HTTP_200;

    def printMsg(msg):
        f = open('api.log','w')
        f.write('hi there\n')
        f.close()