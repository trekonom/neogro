
<!-- README.md is generated from README.Rmd. Please edit README.Rmd -->

# neogro

`neogro` is an R package that implements fast C++ (via Rcpp) solvers for
the **deterministic neoclassical growth model** using value function
iteration. The package provides tools to compute value and policy
functions for a standard Cobb–Douglas economy.

## Installation

You can install the development version from GitHub:

``` r
# install.packages("devtools")
devtools::install_github("trekonom/neogro")
```

``` r
library(neogro)

# Solve the model with default parameters
result <- rcpp_neogro()
```

    ## iteration over value function: 1 error: 0.0213039
    ## iteration over value function: 2 error: 0.0206063
    ## iteration over value function: 3 error: 0.0199405
    ## iteration over value function: 4 error: 0.0193048
    ## iteration over value function: 5 error: 0.0186971
    ## iteration over value function: 6 error: 0.0181159
    ## iteration over value function: 7 error: 0.0175596
    ## iteration over value function: 8 error: 0.0170267
    ## iteration over value function: 9 error: 0.0165159
    ## iteration over value function: 10 error: 0.016026
    ## iteration over value function: 11 error: 0.0155559
    ## iteration over value function: 12 error: 0.0151044
    ## iteration over value function: 13 error: 0.0146706
    ## iteration over value function: 14 error: 0.0142535
    ## iteration over value function: 15 error: 0.0138524
    ## iteration over value function: 16 error: 0.0134663
    ## iteration over value function: 17 error: 0.0130945
    ## iteration over value function: 18 error: 0.0127363
    ## iteration over value function: 19 error: 0.0123911
    ## iteration over value function: 20 error: 0.0120583
    ## iteration over value function: 21 error: 0.0117371
    ## iteration over value function: 22 error: 0.0114272
    ## iteration over value function: 23 error: 0.011128
    ## iteration over value function: 24 error: 0.010839
    ## iteration over value function: 25 error: 0.0105597
    ## iteration over value function: 26 error: 0.0102897
    ## iteration over value function: 27 error: 0.0100286
    ## iteration over value function: 28 error: 0.00977609
    ## iteration over value function: 29 error: 0.00953169
    ## iteration over value function: 30 error: 0.00929512
    ## iteration over value function: 31 error: 0.00906603
    ## iteration over value function: 32 error: 0.00884412
    ## iteration over value function: 33 error: 0.0086291
    ## iteration over value function: 34 error: 0.00842069
    ## iteration over value function: 35 error: 0.00821862
    ## iteration over value function: 36 error: 0.00802266
    ## iteration over value function: 37 error: 0.00783256
    ## iteration over value function: 38 error: 0.00764809
    ## iteration over value function: 39 error: 0.00746904
    ## iteration over value function: 40 error: 0.00729521
    ## iteration over value function: 41 error: 0.00712639
    ## iteration over value function: 42 error: 0.00696242
    ## iteration over value function: 43 error: 0.0068031
    ## iteration over value function: 44 error: 0.00664828
    ## iteration over value function: 45 error: 0.00649778
    ## iteration over value function: 46 error: 0.00635146
    ## iteration over value function: 47 error: 0.00620917
    ## iteration over value function: 48 error: 0.00607077
    ## iteration over value function: 49 error: 0.00593612
    ## iteration over value function: 50 error: 0.0058051
    ## iteration over value function: 51 error: 0.00567758
    ## iteration over value function: 52 error: 0.00555345
    ## iteration over value function: 53 error: 0.00543259
    ## iteration over value function: 54 error: 0.0053149
    ## iteration over value function: 55 error: 0.00520026
    ## iteration over value function: 56 error: 0.00508859
    ## iteration over value function: 57 error: 0.00497979
    ## iteration over value function: 58 error: 0.00487376
    ## iteration over value function: 59 error: 0.00477042
    ## iteration over value function: 60 error: 0.00466968
    ## iteration over value function: 61 error: 0.00457146
    ## iteration over value function: 62 error: 0.00447569
    ## iteration over value function: 63 error: 0.00438228
    ## iteration over value function: 64 error: 0.00429117
    ## iteration over value function: 65 error: 0.00420229
    ## iteration over value function: 66 error: 0.00411557
    ## iteration over value function: 67 error: 0.00403095
    ## iteration over value function: 68 error: 0.00394836
    ## iteration over value function: 69 error: 0.00386775
    ## iteration over value function: 70 error: 0.00378906
    ## iteration over value function: 71 error: 0.00371222
    ## iteration over value function: 72 error: 0.0036372
    ## iteration over value function: 73 error: 0.00356393
    ## iteration over value function: 74 error: 0.00349237
    ## iteration over value function: 75 error: 0.00342247
    ## iteration over value function: 76 error: 0.00335419
    ## iteration over value function: 77 error: 0.00328747
    ## iteration over value function: 78 error: 0.00322227
    ## iteration over value function: 79 error: 0.00315856
    ## iteration over value function: 80 error: 0.0030963
    ## iteration over value function: 81 error: 0.00303543
    ## iteration over value function: 82 error: 0.00297593
    ## iteration over value function: 83 error: 0.00291777
    ## iteration over value function: 84 error: 0.00286089
    ## iteration over value function: 85 error: 0.00280528
    ## iteration over value function: 86 error: 0.00275089
    ## iteration over value function: 87 error: 0.0026977
    ## iteration over value function: 88 error: 0.00264567
    ## iteration over value function: 89 error: 0.00259478
    ## iteration over value function: 90 error: 0.00254499
    ## iteration over value function: 91 error: 0.00249627
    ## iteration over value function: 92 error: 0.00244861
    ## iteration over value function: 93 error: 0.00240197
    ## iteration over value function: 94 error: 0.00235633
    ## iteration over value function: 95 error: 0.00231166
    ## iteration over value function: 96 error: 0.00226793
    ## iteration over value function: 97 error: 0.00222513
    ## iteration over value function: 98 error: 0.00218324
    ## iteration over value function: 99 error: 0.00214222
    ## iteration over value function: 100 error: 0.00210206
    ## iteration over value function: 101 error: 0.00206274
    ## iteration over value function: 102 error: 0.00202423
    ## iteration over value function: 103 error: 0.00198653
    ## iteration over value function: 104 error: 0.0019496
    ## iteration over value function: 105 error: 0.00191343
    ## iteration over value function: 106 error: 0.00187801
    ## iteration over value function: 107 error: 0.00184331
    ## iteration over value function: 108 error: 0.00180931
    ## iteration over value function: 109 error: 0.00177601
    ## iteration over value function: 110 error: 0.00174338
    ## iteration over value function: 111 error: 0.00171142
    ## iteration over value function: 112 error: 0.00168009
    ## iteration over value function: 113 error: 0.0016494
    ## iteration over value function: 114 error: 0.00161932
    ## iteration over value function: 115 error: 0.00158984
    ## iteration over value function: 116 error: 0.00156095
    ## iteration over value function: 117 error: 0.00153263
    ## iteration over value function: 118 error: 0.00150488
    ## iteration over value function: 119 error: 0.00147767
    ## iteration over value function: 120 error: 0.001451
    ## iteration over value function: 121 error: 0.00142486
    ## iteration over value function: 122 error: 0.00139922
    ## iteration over value function: 123 error: 0.00137409
    ## iteration over value function: 124 error: 0.00134945
    ## iteration over value function: 125 error: 0.00132529
    ## iteration over value function: 126 error: 0.0013016
    ## iteration over value function: 127 error: 0.00127836
    ## iteration over value function: 128 error: 0.00125558
    ## iteration over value function: 129 error: 0.00123324
    ## iteration over value function: 130 error: 0.00121132
    ## iteration over value function: 131 error: 0.00118983
    ## iteration over value function: 132 error: 0.00116875
    ## iteration over value function: 133 error: 0.00114807
    ## iteration over value function: 134 error: 0.00112778
    ## iteration over value function: 135 error: 0.00110788
    ## iteration over value function: 136 error: 0.00108836
    ## iteration over value function: 137 error: 0.00106921
    ## iteration over value function: 138 error: 0.00105042
    ## iteration over value function: 139 error: 0.00103199
    ## iteration over value function: 140 error: 0.0010139
    ## iteration over value function: 141 error: 0.000996154
    ## iteration over value function: 142 error: 0.00097874
    ## iteration over value function: 143 error: 0.000961651
    ## iteration over value function: 144 error: 0.000944882
    ## iteration over value function: 145 error: 0.000928426
    ## iteration over value function: 146 error: 0.000912277
    ## iteration over value function: 147 error: 0.000896427
    ## iteration over value function: 148 error: 0.000880871
    ## iteration over value function: 149 error: 0.000865603
    ## iteration over value function: 150 error: 0.000850618
    ## iteration over value function: 151 error: 0.000835909
    ## iteration over value function: 152 error: 0.00082147
    ## iteration over value function: 153 error: 0.000807298
    ## iteration over value function: 154 error: 0.000793385
    ## iteration over value function: 155 error: 0.000779727
    ## iteration over value function: 156 error: 0.000766319
    ## iteration over value function: 157 error: 0.000753156
    ## iteration over value function: 158 error: 0.000740233
    ## iteration over value function: 159 error: 0.000727545
    ## iteration over value function: 160 error: 0.000715087
    ## iteration over value function: 161 error: 0.000702856
    ## iteration over value function: 162 error: 0.000690846
    ## iteration over value function: 163 error: 0.000679054
    ## iteration over value function: 164 error: 0.000667474
    ## iteration over value function: 165 error: 0.000656104
    ## iteration over value function: 166 error: 0.000644938
    ## iteration over value function: 167 error: 0.000633972
    ## iteration over value function: 168 error: 0.000623204
    ## iteration over value function: 169 error: 0.000612629
    ## iteration over value function: 170 error: 0.000602243
    ## iteration over value function: 171 error: 0.000592042
    ## iteration over value function: 172 error: 0.000582024
    ## iteration over value function: 173 error: 0.000572185
    ## iteration over value function: 174 error: 0.00056252
    ## iteration over value function: 175 error: 0.000553028
    ## iteration over value function: 176 error: 0.000543703
    ## iteration over value function: 177 error: 0.000534545
    ## iteration over value function: 178 error: 0.000525548
    ## iteration over value function: 179 error: 0.000516711
    ## iteration over value function: 180 error: 0.00050803
    ## iteration over value function: 181 error: 0.000499501
    ## iteration over value function: 182 error: 0.000491124
    ## iteration over value function: 183 error: 0.000482893
    ## iteration over value function: 184 error: 0.000474807
    ## iteration over value function: 185 error: 0.000466863
    ## iteration over value function: 186 error: 0.000459059
    ## iteration over value function: 187 error: 0.000451391
    ## iteration over value function: 188 error: 0.000443857
    ## iteration over value function: 189 error: 0.000436455
    ## iteration over value function: 190 error: 0.000429182
    ## iteration over value function: 191 error: 0.000422036
    ## iteration over value function: 192 error: 0.000415014
    ## iteration over value function: 193 error: 0.000408114
    ## iteration over value function: 194 error: 0.000401335
    ## iteration over value function: 195 error: 0.000394672
    ## iteration over value function: 196 error: 0.000388126
    ## iteration over value function: 197 error: 0.000381692
    ## iteration over value function: 198 error: 0.00037537
    ## iteration over value function: 199 error: 0.000369158
    ## iteration over value function: 200 error: 0.000363052
    ## iteration over value function: 201 error: 0.000357052
    ## iteration over value function: 202 error: 0.000351155
    ## iteration over value function: 203 error: 0.00034536
    ## iteration over value function: 204 error: 0.000339664
    ## iteration over value function: 205 error: 0.000334066
    ## iteration over value function: 206 error: 0.000328564
    ## iteration over value function: 207 error: 0.000323156
    ## iteration over value function: 208 error: 0.000317841
    ## iteration over value function: 209 error: 0.000312617
    ## iteration over value function: 210 error: 0.000307483
    ## iteration over value function: 211 error: 0.000302435
    ## iteration over value function: 212 error: 0.000297474
    ## iteration over value function: 213 error: 0.000292598
    ## iteration over value function: 214 error: 0.000287804
    ## iteration over value function: 215 error: 0.000283092
    ## iteration over value function: 216 error: 0.000278461
    ## iteration over value function: 217 error: 0.000273907
    ## iteration over value function: 218 error: 0.000269432
    ## iteration over value function: 219 error: 0.000265032
    ## iteration over value function: 220 error: 0.000260706
    ## iteration over value function: 221 error: 0.000256454
    ## iteration over value function: 222 error: 0.000252273
    ## iteration over value function: 223 error: 0.000248163
    ## iteration over value function: 224 error: 0.000244123
    ## iteration over value function: 225 error: 0.000240151
    ## iteration over value function: 226 error: 0.000236245
    ## iteration over value function: 227 error: 0.000232406
    ## iteration over value function: 228 error: 0.000228631
    ## iteration over value function: 229 error: 0.000224919
    ## iteration over value function: 230 error: 0.00022127
    ## iteration over value function: 231 error: 0.000217682
    ## iteration over value function: 232 error: 0.000214154
    ## iteration over value function: 233 error: 0.000210685
    ## iteration over value function: 234 error: 0.000207275
    ## iteration over value function: 235 error: 0.000203921
    ## iteration over value function: 236 error: 0.000200624
    ## iteration over value function: 237 error: 0.000197381
    ## iteration over value function: 238 error: 0.000194193
    ## iteration over value function: 239 error: 0.000191058
    ## iteration over value function: 240 error: 0.000187975
    ## iteration over value function: 241 error: 0.000184943
    ## iteration over value function: 242 error: 0.000181962
    ## iteration over value function: 243 error: 0.000179031
    ## iteration over value function: 244 error: 0.000176148
    ## iteration over value function: 245 error: 0.000173313
    ## iteration over value function: 246 error: 0.000170525
    ## iteration over value function: 247 error: 0.000167784
    ## iteration over value function: 248 error: 0.000165088
    ## iteration over value function: 249 error: 0.000162436
    ## iteration over value function: 250 error: 0.000159829
    ## iteration over value function: 251 error: 0.000157264
    ## iteration over value function: 252 error: 0.000154742
    ## iteration over value function: 253 error: 0.000152262
    ## iteration over value function: 254 error: 0.000149822
    ## iteration over value function: 255 error: 0.000147423
    ## iteration over value function: 256 error: 0.000145063
    ## iteration over value function: 257 error: 0.000142742
    ## iteration over value function: 258 error: 0.00014046
    ## iteration over value function: 259 error: 0.000138215
    ## iteration over value function: 260 error: 0.000136007
    ## iteration over value function: 261 error: 0.000133835
    ## iteration over value function: 262 error: 0.000131698
    ## iteration over value function: 263 error: 0.000129597
    ## iteration over value function: 264 error: 0.000127531
    ## iteration over value function: 265 error: 0.000125498
    ## iteration over value function: 266 error: 0.000123498
    ## iteration over value function: 267 error: 0.000121532
    ## iteration over value function: 268 error: 0.000119597
    ## iteration over value function: 269 error: 0.000117694
    ## iteration over value function: 270 error: 0.000115822
    ## iteration over value function: 271 error: 0.000113981
    ## iteration over value function: 272 error: 0.00011217
    ## iteration over value function: 273 error: 0.000110388
    ## iteration over value function: 274 error: 0.000108636
    ## iteration over value function: 275 error: 0.000106912
    ## iteration over value function: 276 error: 0.000105216
    ## iteration over value function: 277 error: 0.000103547
    ## iteration over value function: 278 error: 0.000101906
    ## iteration over value function: 279 error: 0.000100292
    ## iteration over value function: 280 error: 9.87032e-05
    ## iteration over value function: 281 error: 9.71407e-05
    ## iteration over value function: 282 error: 9.56036e-05
    ## iteration over value function: 283 error: 9.40914e-05
    ## iteration over value function: 284 error: 9.26038e-05
    ## iteration over value function: 285 error: 9.11402e-05
    ## iteration over value function: 286 error: 8.97004e-05
    ## iteration over value function: 287 error: 8.82838e-05
    ## iteration over value function: 288 error: 8.68902e-05
    ## iteration over value function: 289 error: 8.55191e-05
    ## iteration over value function: 290 error: 8.41702e-05
    ## iteration over value function: 291 error: 8.28431e-05
    ## iteration over value function: 292 error: 8.15374e-05
    ## iteration over value function: 293 error: 8.02528e-05
    ## iteration over value function: 294 error: 7.89889e-05
    ## iteration over value function: 295 error: 7.77454e-05
    ## iteration over value function: 296 error: 7.65219e-05
    ## iteration over value function: 297 error: 7.53182e-05
    ## iteration over value function: 298 error: 7.41338e-05
    ## iteration over value function: 299 error: 7.29685e-05
    ## iteration over value function: 300 error: 7.18219e-05
    ## iteration over value function: 301 error: 7.06937e-05
    ## iteration over value function: 302 error: 6.95837e-05
    ## iteration over value function: 303 error: 6.84915e-05
    ## iteration over value function: 304 error: 6.74169e-05
    ## iteration over value function: 305 error: 6.63595e-05
    ## iteration over value function: 306 error: 6.5319e-05
    ## iteration over value function: 307 error: 6.42953e-05
    ## iteration over value function: 308 error: 6.32879e-05
    ## iteration over value function: 309 error: 6.22967e-05
    ## iteration over value function: 310 error: 6.13213e-05
    ## iteration over value function: 311 error: 6.03616e-05
    ## iteration over value function: 312 error: 5.94172e-05
    ## iteration over value function: 313 error: 5.84879e-05
    ## iteration over value function: 314 error: 5.75734e-05
    ## iteration over value function: 315 error: 5.66736e-05
    ## iteration over value function: 316 error: 5.57881e-05
    ## iteration over value function: 317 error: 5.49167e-05
    ## iteration over value function: 318 error: 5.40593e-05
    ## iteration over value function: 319 error: 5.32155e-05
    ## iteration over value function: 320 error: 5.23852e-05
    ## iteration over value function: 321 error: 5.15681e-05
    ## iteration over value function: 322 error: 5.07641e-05
    ## iteration over value function: 323 error: 4.99728e-05
    ## iteration over value function: 324 error: 4.91941e-05
    ## iteration over value function: 325 error: 4.84278e-05
    ## iteration over value function: 326 error: 4.76737e-05
    ## iteration over value function: 327 error: 4.69315e-05
    ## iteration over value function: 328 error: 4.62012e-05
    ## iteration over value function: 329 error: 4.54824e-05
    ## iteration over value function: 330 error: 4.47751e-05
    ## iteration over value function: 331 error: 4.4079e-05
    ## iteration over value function: 332 error: 4.33939e-05
    ## iteration over value function: 333 error: 4.27197e-05
    ## iteration over value function: 334 error: 4.20562e-05
    ## iteration over value function: 335 error: 4.14032e-05
    ## iteration over value function: 336 error: 4.07605e-05
    ## iteration over value function: 337 error: 4.0128e-05
    ## iteration over value function: 338 error: 3.95055e-05
    ## iteration over value function: 339 error: 3.88928e-05
    ## iteration over value function: 340 error: 3.82899e-05
    ## iteration over value function: 341 error: 3.76964e-05
    ## iteration over value function: 342 error: 3.71124e-05
    ## iteration over value function: 343 error: 3.65375e-05
    ## iteration over value function: 344 error: 3.59718e-05
    ## iteration over value function: 345 error: 3.5415e-05
    ## iteration over value function: 346 error: 3.48669e-05
    ## iteration over value function: 347 error: 3.43275e-05
    ## iteration over value function: 348 error: 3.37966e-05
    ## iteration over value function: 349 error: 3.32741e-05
    ## iteration over value function: 350 error: 3.27598e-05
    ## iteration over value function: 351 error: 3.22535e-05
    ## iteration over value function: 352 error: 3.17553e-05
    ## iteration over value function: 353 error: 3.12649e-05
    ## iteration over value function: 354 error: 3.07822e-05
    ## iteration over value function: 355 error: 3.03071e-05
    ## iteration over value function: 356 error: 2.98395e-05
    ## iteration over value function: 357 error: 2.93792e-05
    ## iteration over value function: 358 error: 2.89261e-05
    ## iteration over value function: 359 error: 2.84802e-05
    ## iteration over value function: 360 error: 2.80413e-05
    ## iteration over value function: 361 error: 2.76092e-05
    ## iteration over value function: 362 error: 2.71839e-05
    ## iteration over value function: 363 error: 2.67653e-05
    ## iteration over value function: 364 error: 2.63533e-05
    ## iteration over value function: 365 error: 2.59477e-05
    ## iteration over value function: 366 error: 2.55484e-05
    ## iteration over value function: 367 error: 2.51554e-05
    ## iteration over value function: 368 error: 2.47686e-05
    ## iteration over value function: 369 error: 2.43878e-05
    ## iteration over value function: 370 error: 2.4013e-05
    ## iteration over value function: 371 error: 2.3644e-05
    ## iteration over value function: 372 error: 2.32808e-05
    ## iteration over value function: 373 error: 2.29233e-05
    ## iteration over value function: 374 error: 2.25714e-05
    ## iteration over value function: 375 error: 2.22249e-05
    ## iteration over value function: 376 error: 2.18839e-05
    ## iteration over value function: 377 error: 2.15482e-05
    ## iteration over value function: 378 error: 2.12177e-05
    ## iteration over value function: 379 error: 2.08924e-05
    ## iteration over value function: 380 error: 2.05721e-05
    ## iteration over value function: 381 error: 2.02569e-05
    ## iteration over value function: 382 error: 1.99465e-05
    ## iteration over value function: 383 error: 1.9641e-05
    ## iteration over value function: 384 error: 1.93403e-05
    ## iteration over value function: 385 error: 1.90442e-05
    ## iteration over value function: 386 error: 1.87527e-05
    ## iteration over value function: 387 error: 1.84658e-05
    ## iteration over value function: 388 error: 1.81834e-05
    ## iteration over value function: 389 error: 1.79053e-05
    ## iteration over value function: 390 error: 1.76315e-05
    ## iteration over value function: 391 error: 1.7362e-05
    ## iteration over value function: 392 error: 1.70967e-05
    ## iteration over value function: 393 error: 1.68355e-05
    ## iteration over value function: 394 error: 1.65784e-05
    ## iteration over value function: 395 error: 1.63253e-05
    ## iteration over value function: 396 error: 1.6076e-05
    ## iteration over value function: 397 error: 1.58307e-05
    ## iteration over value function: 398 error: 1.55891e-05
    ## iteration over value function: 399 error: 1.53513e-05
    ## iteration over value function: 400 error: 1.51172e-05
    ## iteration over value function: 401 error: 1.48867e-05
    ## iteration over value function: 402 error: 1.46598e-05
    ## iteration over value function: 403 error: 1.44364e-05
    ## iteration over value function: 404 error: 1.42164e-05
    ## iteration over value function: 405 error: 1.39999e-05
    ## iteration over value function: 406 error: 1.37867e-05
    ## iteration over value function: 407 error: 1.35768e-05
    ## iteration over value function: 408 error: 1.33702e-05
    ## iteration over value function: 409 error: 1.31667e-05
    ## iteration over value function: 410 error: 1.29664e-05
    ## iteration over value function: 411 error: 1.27692e-05
    ## iteration over value function: 412 error: 1.2575e-05
    ## iteration over value function: 413 error: 1.23838e-05
    ## iteration over value function: 414 error: 1.21956e-05
    ## iteration over value function: 415 error: 1.20103e-05
    ## iteration over value function: 416 error: 1.18278e-05
    ## iteration over value function: 417 error: 1.16482e-05
    ## iteration over value function: 418 error: 1.14713e-05
    ## iteration over value function: 419 error: 1.12972e-05
    ## iteration over value function: 420 error: 1.11257e-05
    ## iteration over value function: 421 error: 1.09569e-05
    ## iteration over value function: 422 error: 1.07906e-05
    ## iteration over value function: 423 error: 1.0627e-05
    ## iteration over value function: 424 error: 1.04658e-05
    ## iteration over value function: 425 error: 1.03072e-05
    ## iteration over value function: 426 error: 1.01509e-05
    ## iteration over value function: 427 error: 9.99712e-06

``` r
# View the first few rows
head(result)
```

    ##          k     kopt     copt         ropt
    ## 1 103.1347 103.5797 3.217341 2.602636e-05
    ## 2 104.1713 104.6120 3.231862 2.272825e-05
    ## 3 105.2078 105.6442 3.246311 1.999377e-05
    ## 4 106.2443 106.6765 3.260690 2.391688e-05
    ## 5 107.2809 107.7088 3.275026 1.777524e-05
    ## 6 108.3174 108.7410 3.289280 2.175136e-05

``` r
# Plot the policy function
plot(
  result$k,
  result$kopt - result$k,
  type = "l",
  main = "Policy Function",
  xlab = "Capital (k)",
  ylab = "Next Period Capital (k')"
)
```

![](README_files/figure-gfm/unnamed-chunk-1-1.png)<!-- -->
