#pragma once

#include <vector>

struct MavLambdaParams {
  std::vector<double> ps;
  std::vector<double> pt;
};

inline const MavLambdaParams mavlambda = {
  {0x1.6b7ced7f2e6d5p+6, -0x1.816a132c098e9p+7, 0x1.5884f1a6d403dp+7, -0x1.4d3b20c236c80p+6, 0x1.7156fa509bf87p+4, -0x1.d2b74df0ad967p+1, 0x1.381004fe10765p-2, -0x1.56365dccc78fep-7},
  {0x1.46fcd97d65d90p+10, -0x1.6f8e2ba182eb3p+11, 0x1.60b3a45b8de57p+11, -0x1.7a2ca20e0bd28p+10, 0x1.f06015870cf7bp+8, -0x1.991384cec2440p+6, 0x1.9e2833d45e159p+3, -0x1.d7b2e01c42a84p-1, 0x1.cf5c865bf66a6p-6}
};
