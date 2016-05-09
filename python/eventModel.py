import mongoengine as mongo
import json
import inspect

class EventModel(mongo.Document):
	type = mongo.StringField(required=True)
	value = mongo.StringField(required=True)

	def from_json (self, json_map):
		self.type = json_map['type'];
		self.value = json_map['value'];

	def obj_dict(self):
		timestamp = self.id.generation_time.strftime("%s")
		dict= {}
		dict['timestamp']=long(timestamp)*1000;
		dict['type']=self.type
		dict['value']=self.value
		return dict;