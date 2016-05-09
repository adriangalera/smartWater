#app.py
import falcon
import event
import mongoengine as mongo



def crossdomain(req, resp):
    resp.set_header('Access-Control-Allow-Origin', '*')


api = application = falcon.API(after=[crossdomain])

# DB
mongo.connect('water')

event = event.Event();
api.add_route("/event",event);


