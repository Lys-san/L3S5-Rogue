#include "colors.h"

MLV_Color addOpacity(MLV_Color color, Uint8 alpha) {
	Uint8 rgba[4];

	/*store the informations of the given color so we can modify it*/
	MLV_convert_color_to_rgba(color, &rgba[0], &rgba[1], &rgba[2], &rgba[3]);

	return MLV_convert_rgba_to_color(rgba[0], rgba[1], rgba[2], rgba[3] + alpha);
}


MLV_Color avgOfColors(MLV_Color color1, MLV_Color color2) {
	Uint8 rgbaColor1[4], rgbaColor2[4];

	MLV_convert_color_to_rgba(color1, &rgbaColor1[0], &rgbaColor1[1], &rgbaColor1[2], &rgbaColor1[3]);
	MLV_convert_color_to_rgba(color2, &rgbaColor2[0], &rgbaColor2[1], &rgbaColor2[2], &rgbaColor2[3]);

	return MLV_convert_rgba_to_color(
		AVG(rgbaColor1[0], rgbaColor2[0]),
		AVG(rgbaColor1[1], rgbaColor2[1]),
		AVG(rgbaColor1[2], rgbaColor2[2]),
		AVG(rgbaColor1[3], rgbaColor2[3])
		);
}