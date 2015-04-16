xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 240;
 0.00000;0.90270;-0.14569;,
 0.00000;0.99745;-0.12684;,
 0.03601;0.90270;-0.12684;,
 -0.03601;0.90270;-0.12684;,
 0.03601;0.90270;-0.12684;,
 0.00000;0.99745;-0.12684;,
 0.00000;1.27960;0.10262;,
 0.06653;0.90270;-0.07317;,
 0.00000;0.99745;-0.12684;,
 -0.03601;0.90270;-0.12684;,
 -0.06653;0.90270;-0.07317;,
 0.00000;1.27960;0.10262;,
 0.00000;0.98071;0.04824;,
 0.08693;0.90270;0.00716;,
 -0.08693;0.90270;0.00716;,
 0.00000;0.98071;0.04824;,
 0.00000;1.15031;0.24065;,
 0.09409;0.90270;0.10192;,
 -0.09409;0.90270;0.10192;,
 0.00000;1.15031;0.24065;,
 0.00000;0.92873;0.25439;,
 0.08693;0.85469;0.19668;,
 -0.08693;0.85469;0.19668;,
 0.00000;0.92873;0.25439;,
 0.00000;0.97850;0.37169;,
 0.06653;0.80341;0.27701;,
 -0.06653;0.80341;0.27701;,
 0.00000;0.97850;0.37169;,
 0.06653;0.80341;0.27701;,
 0.00000;0.97850;0.37169;,
 0.00000;0.82272;0.33069;,
 0.03601;0.72796;0.33069;,
 -0.06653;0.80341;0.27701;,
 -0.03601;0.72796;0.33069;,
 0.00000;0.72796;0.34954;,
 0.00000;0.50630;-0.43623;,
 0.00000;0.72521;-0.61365;,
 0.12364;0.58868;-0.40041;,
 0.12364;0.58868;-0.40041;,
 0.00000;0.72521;-0.61365;,
 0.07641;0.72197;-0.34246;,
 0.07641;0.72197;-0.34246;,
 0.00000;0.72521;-0.61365;,
 -0.07641;0.72197;-0.34246;,
 -0.07641;0.72197;-0.34246;,
 0.00000;0.72521;-0.61365;,
 -0.12364;0.58868;-0.40041;,
 -0.12364;0.58868;-0.40041;,
 0.00000;0.62552;-0.38439;,
 0.00000;0.50630;-0.43623;,
 0.12364;0.58868;-0.40041;,
 0.07641;0.72197;-0.34246;,
 -0.07641;0.72197;-0.34246;,
 -0.12364;0.58868;-0.40041;,
 -0.26682;0.24071;-0.49375;,
 -0.34763;0.30162;-0.41453;,
 -0.24969;0.31949;-0.49745;,
 -0.34763;0.30162;-0.41453;,
 -0.21989;0.31310;-0.42272;,
 -0.24969;0.31949;-0.49745;,
 -0.13908;0.25219;-0.50194;,
 -0.13908;0.25219;-0.50194;,
 -0.26123;0.12291;-0.41380;,
 -0.37551;0.20905;-0.30177;,
 -0.34763;0.30162;-0.41453;,
 -0.26682;0.24071;-0.49375;,
 -0.37551;0.20905;-0.30177;,
 -0.19486;0.22528;-0.31336;,
 -0.19486;0.22528;-0.31336;,
 -0.08058;0.13915;-0.42539;,
 -0.13908;0.25219;-0.50194;,
 -0.21989;0.31310;-0.42272;,
 -0.08058;0.13915;-0.42539;,
 -0.26123;0.12291;-0.41380;,
 -0.23620;0.03510;-0.30443;,
 -0.31701;0.09601;-0.22522;,
 -0.31701;0.09601;-0.22522;,
 -0.18927;0.10749;-0.23341;,
 -0.19486;0.22528;-0.31336;,
 -0.37551;0.20905;-0.30177;,
 -0.18927;0.10749;-0.23341;,
 -0.10846;0.04658;-0.31263;,
 -0.10846;0.04658;-0.31263;,
 -0.23620;0.03510;-0.30443;,
 -0.26123;0.12291;-0.41380;,
 -0.08058;0.13915;-0.42539;,
 -0.20639;0.02871;-0.22971;,
 -0.31701;0.09601;-0.22522;,
 -0.20639;0.02871;-0.22971;,
 -0.10846;0.04658;-0.31263;,
 0.24969;0.31949;-0.49745;,
 0.34763;0.30162;-0.41453;,
 0.26682;0.24071;-0.49375;,
 0.24969;0.31949;-0.49745;,
 0.21989;0.31310;-0.42272;,
 0.34763;0.30162;-0.41453;,
 0.13908;0.25219;-0.50194;,
 0.13908;0.25219;-0.50194;,
 0.26682;0.24071;-0.49375;,
 0.34763;0.30162;-0.41453;,
 0.37551;0.20905;-0.30177;,
 0.26123;0.12291;-0.41380;,
 0.19486;0.22528;-0.31336;,
 0.37551;0.20905;-0.30177;,
 0.21989;0.31310;-0.42272;,
 0.13908;0.25219;-0.50194;,
 0.08058;0.13915;-0.42539;,
 0.19486;0.22528;-0.31336;,
 0.26123;0.12291;-0.41380;,
 0.08058;0.13915;-0.42539;,
 0.31701;0.09601;-0.22522;,
 0.23620;0.03510;-0.30443;,
 0.37551;0.20905;-0.30177;,
 0.19486;0.22528;-0.31336;,
 0.18927;0.10749;-0.23341;,
 0.31701;0.09601;-0.22522;,
 0.10846;0.04658;-0.31263;,
 0.18927;0.10749;-0.23341;,
 0.08058;0.13915;-0.42539;,
 0.26123;0.12291;-0.41380;,
 0.23620;0.03510;-0.30443;,
 0.10846;0.04658;-0.31263;,
 0.31701;0.09601;-0.22522;,
 0.20639;0.02871;-0.22971;,
 0.20639;0.02871;-0.22971;,
 0.10846;0.04658;-0.31263;,
 -0.40199;0.22284;0.07641;,
 -0.45715;0.38433;-0.05716;,
 -0.37608;0.31997;-0.12524;,
 -0.45715;0.38433;-0.05716;,
 -0.37293;0.54582;-0.14974;,
 -0.37608;0.31997;-0.12524;,
 -0.37293;0.54582;-0.14974;,
 -0.31777;0.38433;-0.01617;,
 -0.37608;0.31997;-0.12524;,
 -0.40199;0.22284;0.07641;,
 -0.43548;0.31132;0.33707;,
 -0.51349;0.53970;0.14818;,
 -0.39439;0.76808;0.01725;,
 -0.37293;0.54582;-0.14974;,
 -0.39439;0.76808;0.01725;,
 -0.31638;0.53970;0.20614;,
 -0.43548;0.31132;0.33707;,
 -0.45694;0.53358;0.50407;,
 -0.51210;0.69507;0.37050;,
 -0.42788;0.85657;0.27791;,
 -0.42788;0.85657;0.27791;,
 -0.37272;0.69507;0.41148;,
 -0.45694;0.53358;0.50407;,
 -0.45379;0.75943;0.47956;,
 -0.45379;0.75943;0.47956;,
 -0.45379;0.75943;0.47956;,
 -0.45694;0.53358;0.50407;,
 -0.37272;0.69507;0.41148;,
 0.00000;0.94218;0.00000;,
 0.23266;0.84669;-0.14695;,
 0.00000;0.84669;-0.29389;,
 0.23266;0.84669;0.14695;,
 0.00000;0.84669;0.29389;,
 -0.23266;0.84669;0.14695;,
 -0.23266;0.84669;-0.14695;,
 0.00000;0.84669;-0.29389;,
 0.23266;0.84669;-0.14695;,
 0.37646;0.59669;-0.23776;,
 0.00000;0.59669;-0.47553;,
 0.23266;0.84669;-0.14695;,
 0.23266;0.84669;0.14695;,
 0.37646;0.59669;0.23776;,
 0.37646;0.59669;-0.23776;,
 0.23266;0.84669;0.14695;,
 0.00000;0.84669;0.29389;,
 0.00000;0.51639;0.45408;,
 0.37646;0.59669;0.23776;,
 -0.23266;0.84669;0.14695;,
 -0.37646;0.59669;0.23776;,
 -0.23266;0.84669;0.14695;,
 -0.23266;0.84669;-0.14695;,
 -0.37646;0.59669;-0.23776;,
 -0.37646;0.59669;0.23776;,
 -0.23266;0.84669;-0.14695;,
 -0.37646;0.59669;-0.23776;,
 0.37646;0.28768;-0.23776;,
 0.00000;0.28768;-0.47553;,
 0.37646;0.28768;0.23776;,
 0.37646;0.28768;-0.23776;,
 0.00000;0.51639;0.45408;,
 0.00000;0.49199;0.72423;,
 0.00000;0.51639;0.45408;,
 -0.37646;0.28768;0.23776;,
 0.00000;0.49199;0.72423;,
 -0.37646;0.28768;-0.23776;,
 -0.37646;0.28768;-0.23776;,
 0.23266;0.03768;-0.14695;,
 0.00000;0.03768;-0.29389;,
 0.23266;0.03768;0.14695;,
 0.23266;0.03768;-0.14695;,
 0.37646;0.28768;0.23776;,
 0.00000;0.49199;0.72423;,
 0.00000;0.10614;0.35403;,
 0.23266;0.03768;0.14695;,
 -0.37646;0.28768;0.23776;,
 -0.23266;0.03768;0.14695;,
 -0.23266;0.03768;-0.14695;,
 -0.23266;0.03768;0.14695;,
 -0.23266;0.03768;-0.14695;,
 0.00000;0.03768;-0.29389;,
 0.23266;0.03768;-0.14695;,
 0.00000;-0.05781;-0.00000;,
 0.23266;0.03768;0.14695;,
 0.00000;0.10614;0.35403;,
 -0.23266;0.03768;0.14695;,
 -0.23266;0.03768;-0.14695;,
 0.37608;0.31997;-0.12524;,
 0.45715;0.38433;-0.05716;,
 0.40199;0.22284;0.07641;,
 0.37608;0.31997;-0.12524;,
 0.37293;0.54582;-0.14974;,
 0.45715;0.38433;-0.05716;,
 0.37608;0.31997;-0.12524;,
 0.31777;0.38433;-0.01617;,
 0.37293;0.54582;-0.14974;,
 0.40199;0.22284;0.07641;,
 0.51349;0.53970;0.14818;,
 0.43548;0.31132;0.33707;,
 0.37293;0.54582;-0.14974;,
 0.39439;0.76808;0.01725;,
 0.31638;0.53970;0.20614;,
 0.39439;0.76808;0.01725;,
 0.43548;0.31132;0.33707;,
 0.51210;0.69507;0.37050;,
 0.45694;0.53358;0.50407;,
 0.42788;0.85657;0.27791;,
 0.37272;0.69507;0.41148;,
 0.42788;0.85657;0.27791;,
 0.45694;0.53358;0.50407;,
 0.45379;0.75943;0.47956;,
 0.45379;0.75943;0.47956;,
 0.37272;0.69507;0.41148;,
 0.45694;0.53358;0.50407;,
 0.45379;0.75943;0.47956;;
 
 120;
 3;0,1,2;,
 3;0,3,1;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;7,6,12,13;,
 4;11,10,14,15;,
 4;13,12,16,17;,
 4;15,14,18,19;,
 4;17,16,20,21;,
 4;19,18,22,23;,
 4;21,20,24,25;,
 4;23,22,26,27;,
 4;28,29,30,31;,
 4;29,32,33,30;,
 3;31,30,34;,
 3;30,33,34;,
 3;35,36,37;,
 3;38,39,40;,
 3;41,42,43;,
 3;44,45,46;,
 3;47,36,35;,
 3;48,49,50;,
 3;48,50,51;,
 3;48,51,52;,
 3;48,52,53;,
 3;48,53,49;,
 3;54,55,56;,
 3;57,58,59;,
 3;58,60,59;,
 3;61,54,56;,
 4;62,63,64,65;,
 4;66,67,58,57;,
 4;68,69,70,71;,
 4;72,73,54,61;,
 4;74,75,63,62;,
 4;76,77,78,79;,
 4;80,81,69,68;,
 4;82,83,84,85;,
 3;86,87,83;,
 3;88,77,76;,
 3;88,89,77;,
 3;86,83,82;,
 3;90,91,92;,
 3;93,94,95;,
 3;93,96,94;,
 3;90,92,97;,
 4;98,99,100,101;,
 4;95,94,102,103;,
 4;104,105,106,107;,
 4;97,92,108,109;,
 4;101,100,110,111;,
 4;112,113,114,115;,
 4;107,106,116,117;,
 4;118,119,120,121;,
 3;120,122,123;,
 3;115,114,124;,
 3;114,125,124;,
 3;121,120,123;,
 3;126,127,128;,
 3;129,130,131;,
 3;132,133,134;,
 3;133,135,134;,
 4;136,137,127,126;,
 4;137,138,139,127;,
 4;140,141,133,132;,
 4;141,142,135,133;,
 4;143,144,137,136;,
 4;144,145,138,137;,
 4;146,147,141,140;,
 4;147,148,142,141;,
 3;149,144,143;,
 3;149,145,144;,
 3;150,147,146;,
 3;151,152,153;,
 3;154,155,156;,
 3;154,157,155;,
 3;154,158,157;,
 3;154,159,158;,
 3;154,160,159;,
 3;154,156,160;,
 4;161,162,163,164;,
 4;165,166,167,168;,
 4;169,170,171,172;,
 4;170,173,174,171;,
 4;175,176,177,178;,
 4;179,161,164,180;,
 4;164,163,181,182;,
 4;168,167,183,184;,
 4;167,185,186,183;,
 4;187,178,188,189;,
 4;178,177,190,188;,
 4;180,164,182,191;,
 4;182,181,192,193;,
 4;184,183,194,195;,
 4;196,197,198,199;,
 4;197,200,201,198;,
 4;188,190,202,203;,
 4;191,182,193,204;,
 3;205,206,207;,
 3;206,208,207;,
 3;208,209,207;,
 3;209,210,207;,
 3;210,211,207;,
 3;211,205,207;,
 3;212,213,214;,
 3;215,216,217;,
 3;218,219,220;,
 3;218,221,219;,
 4;214,213,222,223;,
 4;213,224,225,222;,
 4;220,219,226,227;,
 4;219,221,228,226;,
 4;223,222,229,230;,
 4;222,225,231,229;,
 4;227,226,232,233;,
 4;226,228,234,232;,
 3;230,229,235;,
 3;229,231,235;,
 3;233,232,236;,
 3;237,238,239;;
 
 MeshMaterialList {
  1;
  120;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "res/x/tori.png";
   }
  }
 }
 MeshTextureCoords {
  240;
  0.631180;0.270850;,
  0.631180;0.239110;,
  0.643230;0.270850;,
  0.619120;0.270850;,
  0.008960;0.943050;,
  0.008960;0.911310;,
  0.085810;0.816830;,
  0.026940;0.943050;,
  0.516000;0.921070;,
  0.516000;0.952800;,
  0.498030;0.952800;,
  0.439160;0.826580;,
  0.067590;0.916920;,
  0.053840;0.943050;,
  0.471130;0.952800;,
  0.457370;0.926670;,
  0.132030;0.860120;,
  0.085570;0.943050;,
  0.439390;0.952800;,
  0.392930;0.869870;,
  0.136630;0.934330;,
  0.117310;0.959130;,
  0.407660;0.968880;,
  0.388330;0.944080;,
  0.175920;0.917660;,
  0.144210;0.976300;,
  0.380750;0.986050;,
  0.349050;0.927410;,
  0.891900;0.655060;,
  0.914190;0.596420;,
  0.914190;0.648590;,
  0.902130;0.680330;,
  0.936470;0.655060;,
  0.926250;0.680330;,
  0.914190;0.680330;,
  0.864210;0.885660;,
  0.864210;0.812350;,
  0.905610;0.858070;,
  0.317250;0.632390;,
  0.245840;0.586670;,
  0.336660;0.587760;,
  0.873980;0.596420;,
  0.848390;0.687250;,
  0.822800;0.596420;,
  0.585930;0.827660;,
  0.676750;0.826580;,
  0.605330;0.872300;,
  0.822800;0.858070;,
  0.736070;0.942630;,
  0.736070;0.982560;,
  0.694670;0.954970;,
  0.710490;0.910330;,
  0.761660;0.910330;,
  0.777480;0.954970;,
  0.819940;0.538970;,
  0.792870;0.518570;,
  0.825670;0.512580;,
  0.909570;0.550350;,
  0.952350;0.553090;,
  0.942360;0.578110;,
  0.979410;0.579620;,
  0.862720;0.535120;,
  0.919150;0.068810;,
  0.881630;0.039960;,
  0.919400;0.008960;,
  0.945920;0.029360;,
  0.900230;0.512580;,
  0.960730;0.516460;,
  0.308990;0.679720;,
  0.271480;0.708570;,
  0.245840;0.670710;,
  0.272370;0.650320;,
  0.882310;0.572980;,
  0.821810;0.578420;,
  0.882520;0.098220;,
  0.855990;0.077820;,
  0.655770;0.933520;,
  0.612990;0.929670;,
  0.614860;0.890220;,
  0.675360;0.895660;,
  0.335770;0.719170;,
  0.309240;0.739570;,
  0.925840;0.237660;,
  0.883060;0.240400;,
  0.874680;0.203770;,
  0.935170;0.199890;,
  0.893040;0.265420;,
  0.855990;0.266930;,
  0.618720;0.956050;,
  0.585930;0.950070;,
  0.751310;0.826580;,
  0.784100;0.832560;,
  0.757040;0.852960;,
  0.230880;0.989530;,
  0.220900;0.964510;,
  0.263680;0.961770;,
  0.193840;0.991040;,
  0.714260;0.849120;,
  0.193840;0.837220;,
  0.220370;0.816830;,
  0.258130;0.847830;,
  0.220610;0.876670;,
  0.212520;0.927880;,
  0.273020;0.924000;,
  0.886200;0.705170;,
  0.912730;0.725570;,
  0.887100;0.763420;,
  0.849580;0.734580;,
  0.755170;0.892410;,
  0.694670;0.886970;,
  0.283770;0.885680;,
  0.257240;0.906080;,
  0.855990;0.121580;,
  0.916490;0.116140;,
  0.918370;0.155590;,
  0.875590;0.159430;,
  0.849330;0.794420;,
  0.822800;0.774030;,
  0.822800;0.903580;,
  0.883300;0.907460;,
  0.874920;0.944080;,
  0.832140;0.941340;,
  0.901980;0.970610;,
  0.864940;0.969110;,
  0.912630;0.181970;,
  0.945430;0.175990;,
  0.152180;0.798900;,
  0.196910;0.744820;,
  0.219710;0.766380;,
  0.930660;0.759250;,
  0.958860;0.705170;,
  0.957800;0.780800;,
  0.349050;0.700490;,
  0.393780;0.754570;,
  0.357260;0.776130;,
  0.424780;0.808660;,
  0.064880;0.769270;,
  0.128140;0.692790;,
  0.171990;0.616300;,
  0.227920;0.690740;,
  0.404970;0.626060;,
  0.468230;0.702540;,
  0.512080;0.779020;,
  0.008960;0.694840;,
  0.053690;0.640750;,
  0.084700;0.586670;,
  0.492270;0.596420;,
  0.537000;0.650510;,
  0.568000;0.704590;,
  0.017170;0.619200;,
  0.559800;0.628950;,
  0.561080;0.826580;,
  0.562130;0.902210;,
  0.533930;0.848130;,
  0.870790;0.396240;,
  0.948710;0.445450;,
  0.870790;0.494660;,
  0.948710;0.347030;,
  0.870790;0.297820;,
  0.792870;0.347030;,
  0.792870;0.445450;,
  0.475120;0.008960;,
  0.553040;0.008960;,
  0.601200;0.092680;,
  0.475120;0.092680;,
  0.039380;0.008960;,
  0.137800;0.008960;,
  0.168210;0.092680;,
  0.008960;0.092680;,
  0.397200;0.297820;,
  0.475120;0.297820;,
  0.475120;0.408430;,
  0.349050;0.381540;,
  0.553040;0.297820;,
  0.601200;0.381540;,
  0.202290;0.297820;,
  0.300710;0.297820;,
  0.331130;0.381540;,
  0.171880;0.381540;,
  0.397200;0.008960;,
  0.349050;0.092680;,
  0.601200;0.196170;,
  0.475120;0.196170;,
  0.168210;0.196170;,
  0.008960;0.196170;,
  0.240650;0.119580;,
  0.331130;0.127750;,
  0.099430;0.408430;,
  0.171880;0.485030;,
  0.008960;0.416600;,
  0.331130;0.485030;,
  0.349050;0.196170;,
  0.553040;0.279890;,
  0.475120;0.279890;,
  0.137800;0.279890;,
  0.039380;0.279890;,
  0.349050;0.494780;,
  0.475120;0.426360;,
  0.475120;0.555570;,
  0.397200;0.578500;,
  0.601200;0.494780;,
  0.553040;0.578500;,
  0.300710;0.568750;,
  0.202290;0.568750;,
  0.397200;0.279890;,
  0.697030;0.297820;,
  0.774950;0.347030;,
  0.697030;0.396240;,
  0.774950;0.445450;,
  0.697030;0.514800;,
  0.619120;0.445450;,
  0.619120;0.347030;,
  0.594130;0.776130;,
  0.616930;0.754570;,
  0.661660;0.808660;,
  0.924590;0.887980;,
  0.923540;0.812350;,
  0.951740;0.866430;,
  0.829870;0.188660;,
  0.793340;0.167110;,
  0.838070;0.113030;,
  0.762340;0.221190;,
  0.685700;0.702540;,
  0.748960;0.779020;,
  0.585930;0.700490;,
  0.641850;0.626060;,
  0.718890;0.115080;,
  0.782150;0.038590;,
  0.675040;0.191560;,
  0.760150;0.650510;,
  0.804880;0.704590;,
  0.729140;0.596420;,
  0.650120;0.063040;,
  0.694850;0.008960;,
  0.619120;0.117130;,
  0.796670;0.628950;,
  0.627320;0.041490;,
  0.329890;0.838380;,
  0.301690;0.892460;,
  0.302750;0.816830;;
 }
}
