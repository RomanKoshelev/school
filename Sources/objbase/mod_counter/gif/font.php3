<?php
	Header			("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
	Header			("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
	Header			("Cache-Control: no-cache, must-revalidate");
	Header			("Pragma: no-cache");
	Header			("Content-type: image/gif");

	if (!isset($font)) $font=0;
//              0   1 	2	 3	  4	5	 6
	$w = array ( 5,  6,  6,  7,  8,  9, 10);
	$h = array (11, 11, 13, 13, 16, 16, 16);

	$W = $w[$font]*256;
	$H = $h[$font];

	$Image	= ImageCreate			($W, $H);
	$CLR		= ImageColorAllocate	($Image,      0,     0,   0);
	$BGR		= ImageColorAllocate	($Image,		255,   255, 255);

	ImageFilledRectangle	($Image, 0,0, $W, $H, $BGR);

	for ($i=0; $i<256; $i++)
	{
		ImageString ($Image, $font, $i*$w[$font], 0, convert_cyr_string (sprintf("%c", $i),  "w", "k"), $CLR);
	}

	ImageGif		($Image);
	ImageDestroy($Image);

	exit;
//____________________________________________________________________________[]
?>