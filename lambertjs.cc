#include <node.h>
#include <v8.h>


extern "C" {
	#include "lambert/src/lambert.h"	
	#include <math.h>
}


using namespace v8;

bool checkArgue(const Arguments& args)
{
	if(args.Length() <2)
	{
		if (args.Length() < 2) {
		    ThrowException(Exception::TypeError(String::New("Wrong number of arguments!")));
		    return false;
	  }
	}

	if(!args[0]->IsObject() || !args[1]->IsNumber())
	{
		 ThrowException(Exception::TypeError(String::New("Wrong arguments!")));
    	return false;
	}

	Local<Object> jsObj = args[0]->ToObject();	
	if(!jsObj->HasRealNamedProperty(String::New("x")) || !jsObj->HasRealNamedProperty(String::New("y")) || !jsObj->HasRealNamedProperty(String::New("z")))
	{
		 ThrowException(Exception::TypeError(String::New("Object has no property x,y and z!")));
    	return false;
	}

	if(!jsObj->Get(String::New("x"))->IsNumber() || !jsObj->Get(String::New("y"))->IsNumber() || !jsObj->Get(String::New("z"))->IsNumber() )
	{
		
		ThrowException(Exception::TypeError(String::New("x,y and z properties are not all numbers!")));
    	return false;
	}

	long long val = args[1]->ToInteger()->Value();
	
	if(val > 5 || val < 0)
	{
		ThrowException(Exception::TypeError(String::New("Incorrect zone was given!")));
    	 return false;
	}

	return true;
	
}

Handle<Value> lambertTowgs84(const Arguments& args){
	HandleScope scope;

	if(!checkArgue(args))
	{
		return scope.Close(Undefined());
	}
	double lat, lon, h;
	
	Local<Object> jsObj = args[0]->ToObject();	
	
	lon = jsObj->Get(String::New("x"))->NumberValue();
	lat = jsObj->Get(String::New("y"))->NumberValue();
	h = jsObj->Get(String::New("z"))->NumberValue();

	long long val = args[1]->ToInteger()->Value();

	YGLambertZone zone = (YGLambertZone) val;

	YGPoint org = {lon,lat,h,DEGREE},dest = {0,0,0,DEGREE};

	lambert_to_wgs84(&org,&dest,zone);

	Local<Object> point = Object::New();
	point->Set(String::NewSymbol("x"),Number::New(dest.x));
	point->Set(String::NewSymbol("y"),Number::New(dest.y));
	point->Set(String::NewSymbol("z"),Number::New(dest.z));

	return scope.Close(point);

}


Handle<Value> lambertTowgs84Deg(const Arguments& args ){
	HandleScope scope;

	if(!checkArgue(args))
	{
		return scope.Close(Undefined());
	}
	double lat, lon, h;
	
	Local<Object> jsObj = args[0]->ToObject();	
	
	lon = jsObj->Get(String::New("x"))->NumberValue();
	lat = jsObj->Get(String::New("y"))->NumberValue();
	h = jsObj->Get(String::New("z"))->NumberValue();

	long long val = args[1]->ToInteger()->Value();

	YGLambertZone zone = (YGLambertZone) val;

	YGPoint org = {lon,lat,h,DEGREE},dest = {0,0,0,DEGREE};

	lambert_to_wgs84_deg(&org,&dest,zone);

	Local<Object> point = Object::New();
	point->Set(String::NewSymbol("x"),Number::New(dest.x));
	point->Set(String::NewSymbol("y"),Number::New(dest.y));
	point->Set(String::NewSymbol("z"),Number::New(dest.z));

	return scope.Close(point);

}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("lambertTowgs84"),
      FunctionTemplate::New(lambertTowgs84)->GetFunction());
   exports->Set(String::NewSymbol("lambertTowgs84Deg"),
      FunctionTemplate::New(lambertTowgs84Deg)->GetFunction());
   exports->Set(String::NewSymbol("LambertI"),
     Number::New(LAMBERT_I));
     exports->Set(String::NewSymbol("LambertII"),
     Number::New(LAMBERT_II));
       exports->Set(String::NewSymbol("LambertIII"),
     Number::New(LAMBERT_III));
         exports->Set(String::NewSymbol("LambertIV"),
     Number::New(LAMBERT_IV));
           exports->Set(String::NewSymbol("LambertIIExtended"),
     Number::New(LAMBERT_II_E));
             exports->Set(String::NewSymbol("Lambert93"),
     Number::New(LAMBERT_93));

}
NODE_MODULE(lambertjs, init)
