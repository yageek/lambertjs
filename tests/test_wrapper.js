var lambert = require('../build/Release/lambert');

exports['require'] = function (test) {
	test.ok(typeof lambert !== 'undefined',"Import should work");
	test.done();
};

exports['testValue'] = function (test)
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