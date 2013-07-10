var lambert = require('..');

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
exports['testEnum'] = function (test)
{
	test.ok(lambert.LambertI == 0,"LambertI should equal 0");
	test.ok(lambert.LambertII == 1,"LambertII should equal 1");
	test.ok(lambert.LambertIII == 2,"LambertIII should equal 2");
	test.ok(lambert.LambertIV == 3,"LambertIV should equal 3");
	test.ok(lambert.LambertIIExtended == 4, "LambertIIExtended should equal 4");
	test.ok(lambert.Lambert93 == 5, "Lambert93 should equal  5");

	test.done();
}
