#include <node.h>
#include <v8.h>

extern "C" {
	#include "lambert/src/lambert.h"	
}


using namespace v8;


Handle<Value> lambertTowgs84(const Arguments& args){
	HandleScope scope;

	if(args.Length() <2)
	{
		if (args.Length() < 2) {
		    ThrowException(Exception::TypeError(String::New("Wrong number of arguments!")));
		    return scope.Close(Undefined());
	  }
	}

	if(!args[0]->IsObject() || !args[1]->IsNumber())
	{
		 ThrowException(Exception::TypeError(String::New("Wrong arguments!")));
    	 return scope.Close(Undefined());
	}

	Local<Object> jsObj = args[0]->ToObject();	
	if(!jsObj->HasRealNamedProperty(String::New("x")) || !jsObj->HasRealNamedProperty(String::New("y")) || !jsObj->HasRealNamedProperty(String::New("z")))
	{
		 ThrowException(Exception::TypeError(String::New("Object has no property x,y and z!")));
    	 return scope.Close(Undefined());
	}

	double lat, lon, h;

	if(!jsObj->Get(String::New("x"))->IsNumber() || !jsObj->Get(String::New("y"))->IsNumber() || !jsObj->Get(String::New("z"))->IsNumber() )
	{
		
		ThrowException(Exception::TypeError(String::New("x,y and z properties are not all numbers!")));
    	return scope.Close(Undefined());
	}

	lon = jsObj->Get(String::New("x"))->NumberValue();
	lat = jsObj->Get(String::New("y"))->NumberValue();
	h = jsObj->Get(String::New("z"))->NumberValue();


	long long val = args[1]->ToInteger()->Value();
	
	if(val > 5 || val < 0)
	{
		ThrowException(Exception::TypeError(String::New("Incorrect zone was given!")));
    	 return scope.Close(Undefined());
	}
	
	LambertZone zone = (LambertZone) val;
	Point org = {lon,lat,h},dest = {0,0,0};

	lambert_to_wgs84(&org,&dest,zone);

	Local<Object> point = Object::New();
	point->Set(String::NewSymbol("x"),Number::New(dest.x));
	point->Set(String::NewSymbol("y"),Number::New(dest.y));
	point->Set(String::NewSymbol("z"),Number::New(dest.z));

	return scope.Close(point);

}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("lambertTowgs84"),
      FunctionTemplate::New(lambertTowgs84)->GetFunction());
}

NODE_MODULE(lambert, init)
