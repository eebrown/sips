/*=========================================================================
  
  Copyright 2002, 2006-2010, Dr. Sandra Black
  Linda C. Campbell Cognitive Neurology Unit
  Sunnybrook Health Sciences Center
  
  This file is part of the Sunnybrook Image Software Processing (SIPS) package

  SIPS is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

=========================================================================*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include "griddebug.h"

typedef unsigned char uchar;

enum Value {BACKGROUND, GRIDLINE, HIGHLIGHT,
	    LSUPF=3, LIF=4, LOBF=5, LMOBF=6, LSP=7, LIP=8, LO=9, LAT=10, LPT=11,
            LABGT=12, LPBGT=13, LMSF=14, LMIF=15,
	    RSUPF=16, RIF=17, ROBF=18, RMOBF=19, RSP=20, RIP=21, RO=22, RAT=23, RPT=24,
            RABGT=25, RPBGT=26, RMSF=27, RMIF=28,
	    CEREBELLUM=29,
	    LC_LINE = 100, LSC_MARK, LSF_LINE, LOP_LINE,
	    LPT_LINE, LOT_LINE, LOC_LINE, LATPT_LINE,
	    RC_LINE = 120, RSC_MARK, RSF_LINE, ROP_LINE,
	    RPT_LINE, ROT_LINE, ROC_LINE, RATPT_LINE,
	    M_LINE = 140, LM_LINE, RM_LINE,
	    ORB_LINE=150, BASG_LINE, AP_LINE, AP4_LINE};

int LOBE_OFFSET = 13, LINE_OFFSET = 20;

Grid grid;
int sz[3], area, volume;
int lpron, rpron;



enum Direction { XX, _XX, YY, _YY, ZZ, _ZZ};

class dir {
public:
    dir(unsigned char D, int m, int M): d(D), min(m), max(M) {}
    unsigned char d;
    int min;
    int max;
};

#endif
