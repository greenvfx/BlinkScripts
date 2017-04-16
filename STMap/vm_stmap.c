kernel STMapKernel : ImageComputationKernel<ePixelWise>
{
  Image<eRead, eAccessRandom, eEdgeClamped> stmap; // the input image
  Image<eRead, eAccessRandom, eEdgeClamped> src; // the input image
  Image<eWrite, eAccessPoint> dst; // the output image

  param:
    float st_width;
    float st_height;

  void define() {
    defineParam(st_width, "stmap_width", 0.0f);
    defineParam(st_height, "stmap_height", 0.0f);
  }

  void process(int2 pos) {

    float4 uv = stmap(pos.x,pos.y);

    float x = uv.x * st_width;
    float y = uv.y * st_height;
    float4 color = bilinear(src, x, y);
    float alpha = bilinear(stmap, x, y, 3);

    for (int c = 0; c < 3; c++)
            dst(c) = color[c];
        dst(3) = alpha;
  }
};