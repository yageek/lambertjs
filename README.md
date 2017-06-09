# lambertjs

Lambertjs is a wrapper to the lambert C library.

# Install

`npm install lambertjs`
# Usage

```javascript
var lambert = require('lambertjs');

var lambertLoc = {
					x: 994272.661,
					y: 13467.422,
					z: 0
				}

/**
* Zone argument could be one of the followings : 
* LambertI, LambertII, LambertIII, LambertIV, LambertIIExtended, Lambert93
*/

var wsg84Loc = lambert.lambertTowgs84Deg(lambertLoc,lambert.LambertI);
```

#License
Copyright (c) 2013 Yannick Heinrich - Released under the GPLv2 License.
