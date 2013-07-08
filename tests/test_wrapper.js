var lambert = require('../build/Release/lambert');

exports['require'] = function (test) {
	test.ok(typeof lambert !== 'undefined',"Import should work");
	test.done();
};


exports['testFail'] = function (test)
{
	org = {
		x: 1000,
		z: 0
	}
	test.throws(function(){
		dest  = lambert.lambertTowgs84(org,1);
	},Error,"Should fails");
	test.done();
}
exports['testValueRad'] = function (test)
{
	org = {
		x: 1000,
		y: 1000,
		z: 0
	}
	dest  = lambert.lambertTowgs84(org,1);
	console.log("(Rad)X:" + dest.x + " Y:" + dest.y + " Z:" + dest.z);
	test.done();
}

exports['testValueDeg'] = function (test)
{
	org = {
		x: 1000,
		y: 1000,
		z: 0
	}
	dest  = lambert.lambertTowgs84Deg(org,1);
	console.log("(Rad)X:" + dest.x + " Y:" + dest.y + " Z:" + dest.z);
	test.done();
}