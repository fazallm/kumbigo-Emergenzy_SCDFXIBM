import csv
import time
import json

from flask import Flask
from flask_restx import Api, Resource, fields, reqparse

app = Flask(__name__)
api = Api(app, version='1.0', title='Cloud Impact Rating API',
    description='A protoype API system allowing the storage and retrieval of Climate Impact Rating data for products',
    prefix='/v1'
)

from cloudant.client import Cloudant

# You must overwrite the values in api_access below with those from your service credential, that you created in IBM Cloud IAM for Cloudant.
# The actual values below are to just show the format - and these are no longer valid.
api_access = {
  "apikey": "f2E5kcbUfvwV5jq_aUxCTaJYK9CjOb2qpDbgHW4rxWog",
  "host": "c1f96503-6bb4-44d2-bdbe-c74f889a237b-bluemix.cloudantnosqldb.appdomain.cloud",
  "iam_apikey_description": "Auto-generated for key 5d09dece-f039-468a-ae5c-193b67a934dd",
  "iam_apikey_name": "Service credentials-1",
  "iam_role_crn": "crn:v1:bluemix:public:iam::::serviceRole:Manager",
  "iam_serviceid_crn": "crn:v1:bluemix:public:iam-identity::a/30211c6829db4204b116b910e925704f::serviceid:ServiceId-3664b46f-6699-43e4-896b-dfd9ff951df0",
  "password": "eb4ec0b729b60790b97a4d4b19fd628cff923f0fc1f0505eb48c8f2e189c66a4",
  "port": 443,
  "url": "https://c1f96503-6bb4-44d2-bdbe-c74f889a237b-bluemix:eb4ec0b729b60790b97a4d4b19fd628cff923f0fc1f0505eb48c8f2e189c66a4@c1f96503-6bb4-44d2-bdbe-c74f889a237b-bluemix.cloudantnosqldb.appdomain.cloud",
  "username": "c1f96503-6bb4-44d2-bdbe-c74f889a237b-bluemix"
}
client = Cloudant.iam(
    api_access['username'],
    api_access['apikey'],
    connect=True
)

product_ns = api.namespace('emergency', description='CFR Interaction')

# Define the API models we will use (these will show up in the Swagger Specification).

emergency = api.model('Emergency', {
    'id': fields.Integer(),
    'gender': fields.Integer(required=False, description='The efficiency-in-use rating (0-9, where 0 is best) of this item'),
    'height': fields.Float(required=False, description='The energy (J) to produce this item'),
    'age': fields.Integer(required=False, description='The CO2 released (Kg) to produce this item'),
    'event': fields.String(required=False, description='The other green house gases released (Kg) to produce this item'),
    'postalCode': fields.Integer(required=False, description='The volume of water (litres) to produce this item'),
    'phoneCode': fields.Integer(required=False, description='The amout of plastic (Kg) included in this item'),
    'status':fields.String(required=False)
})

responder = api.model('CFRResponder', {
    'id': fields.Integer(),
    'name': fields.String(required=True),
    'phoneNumber': fields.Integer(required=True),
    'age': fields.Integer(required=True, description='The category of this product, with its type'),
    'postalCode': fields.Integer(required=True, description='The model number of this product'),
    'certificate': fields.String(required=True, description='The venfor of this item'),
    'handledCase': fields.Integer()
})

db_name = 'cfr-db'
db_emergency = 'emergency'


class Responder(object):
    def __init__(self):
        if db_name in client.all_dbs():
            self.cfr_db = client[db_name]
        else:
            self.cfr_db = client.create_database(db_name)
            self.import_data()

    def import_data(self):
        print ("Importing dummy data", end = '', flush=True)

        with open('cfr-data.json', 'r') as f:
            x = json.load(f)
            for i in range(len(x)):
                self.create(i, x[i])
        print ("complete")

    def list(self):
        return [x for x in self.cfr_db]

    def get(self, id):
        try:
            my_document = self.cfr_db[id]
            my_document['id'] = my_document['barcode_id']
        except KeyError:
            api.abort(404, "Product {} not registered".format(id))
        return my_document

    def create(self, i, data):
        try:
            data['_id'] = str(i)
            my_document = self.cfr_db.create_document(data)
            print(my_document)
            my_document['id'] = my_document['_id']
        except KeyError:
            api.abort(404, "Product {} already registered".format(id))
        return my_document

    def delete(self, id):
        try:
            my_document = self.cfr_db[id]
            my_document.delete()
        except KeyError:
            api.abort(404, "Product {} not registered".format(id))
        return



class Emergency(object):
    def __init__(self):
        if db_emergency in client.all_dbs():
            self.emergency_db = client[db_emergency]
            self.key = len(self.emergency_db)+1
        
        else:
            # Create the DB and immport the dummy data
            self.emergency_db = client.create_database(db_emergency)
            self.key = 1
            # self.import_data()


    def print_x(self):
        print(self.emergency_db)

    def list(self):
        return [x for x in self.emergency_db]

    def get(self, id):
        try:
            my_document = self.emergency_db[id]
            my_document['id'] = my_document['_id']
        except KeyError:
            api.abort(404, "Product {} not registered".format(id))
        return my_document

    def get_by_postal(self, postalCode):
        try:
            data=[]
            postalCode = int(postalCode)
            for x in self.emergency_db.values():
                if x['postalCode']==postalCode and x['status']=='ACTIVE':    
                    data.append(x)
        except KeyError:
            api.abort(404, "Product {} not registered".format(id))
        return data

    def create(self, data):
        try:
            data['_id'] = str(self.key)
            data['status'] = 'ACTIVE'
            my_document = self.emergency_db.create_document(data)
            my_document['id'] = self.key
            self.key +=1
        except KeyError:
            api.abort(404, "Product {} already registered".format(id))
        return my_document

    def update(self, id):
        data = self.get(id)
        # Not currently supported
        data['status']='INACTIVE'
        self.emergency_db[id] = data
        return data

    def delete(self, id):
        try:
            my_document = self.emergency_db[id]
            my_document.delete()
        except KeyError:
            api.abort(404, "Product {} not registered".format(id))
        return

@product_ns.route('/responder')
class Product(Resource):
    @api.marshal_with(emergency)
    @api.doc('List products')
    @api.doc(params={'postalCode': 'The barcode ID of this product (optional)'})
    def get(self):
        parser = reqparse.RequestParser()
        parser.add_argument('postalCode', required=False, location='args')
        args = parser.parse_args()
        if args['postalCode']:
            return [Emergency().get_by_postal(args['postalCode'])]
        else:
            return Emergency().list()


@product_ns.route('/patient')
class Patient(Resource):
    @api.marshal_with(emergency, code=201)
    @api.doc(body=emergency)
    def post(self):
        return Emergency().create(api.payload), 201

@product_ns.route('/patient/<string:id>')
class ProductWithID(Resource):
    @api.marshal_with(emergency)
    @api.doc(params={'id': 'The unique ID of this product'})
    def get(self, id):
        return Emergency().update(id)

    @api.marshal_with(emergency)
    @api.doc(params={'id': 'The unique ID of this product'})
    def patch(self,id):
        return Emergency().update(id)

if __name__ == '__main__':
	app.run()