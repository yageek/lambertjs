var lambert = require('../build/Release/lambert');

exports['require'] = function (test) {
	test.ok(typeof lambert !== 'undefined',"Import should work");
	test.done();
};