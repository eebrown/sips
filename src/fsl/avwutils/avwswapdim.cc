/*  avwswapdim.cc

    Mark Jenkinson, FMRIB Image Analysis Group

    Copyright (C) 2003-2004 University of Oxford  */

/*  Part of FSL - FMRIB's Software Library
    http://www.fmrib.ox.ac.uk/fsl
    fsl@fmrib.ox.ac.uk
    
    Developed at FMRIB (Oxford Centre for Functional Magnetic Resonance
    Imaging of the Brain), Department of Clinical Neurology, Oxford
    University, Oxford, UK
    
    
    LICENCE
    
    FMRIB Software Library, Release 3.3 (c) 2006, The University of
    Oxford (the "Software")
    
    The Software remains the property of the University of Oxford ("the
    University").
    
    The Software is distributed "AS IS" under this Licence solely for
    non-commercial use in the hope that it will be useful, but in order
    that the University as a charitable foundation protects its assets for
    the benefit of its educational and research purposes, the University
    makes clear that no condition is made or to be implied, nor is any
    warranty given or to be implied, as to the accuracy of the Software,
    or that it will be suitable for any particular purpose or for use
    under any specific conditions. Furthermore, the University disclaims
    all responsibility for the use which is made of the Software. It
    further disclaims any liability for the outcomes arising from using
    the Software.
    
    The Licensee agrees to indemnify the University and hold the
    University harmless from and against any and all claims, damages and
    liabilities asserted by third parties (including claims for
    negligence) which arise directly or indirectly from the use of the
    Software or the sale of any products based on the Software.
    
    No part of the Software may be reproduced, modified, transmitted or
    transferred in any form or by any means, electronic or mechanical,
    without the express permission of the University. The permission of
    the University is not required if the said reproduction, modification,
    transmission or transference is done without financial return, the
    conditions of this Licence are imposed upon the receiver of the
    product, and all original and amended source code is included in any
    transmitted product. You may be held legally responsible for any
    copyright infringement that is caused or encouraged by your failure to
    abide by these terms and conditions.
    
    You are not permitted under this Licence to use this Software
    commercially. Use for which any financial return is received shall be
    defined as commercial use, and includes (1) integration of all or part
    of the source code or the Software into a product for sale or license
    by or on behalf of Licensee to third parties or (2) use of the
    Software or any derivative of it for research with the final aim of
    developing software products for sale or license to a third party or
    (3) use of the Software or any derivative of it for research with the
    final aim of developing non-software products for sale or license to a
    third party, or (4) use of the Software to provide any service to an
    external organisation for which payment is received. If you are
    interested in using the Software commercially, please contact Isis
    Innovation Limited ("Isis"), the technology transfer company of the
    University, to negotiate a licence. Contact details are:
    innovation@isis.ox.ac.uk quoting reference DE/1112. */


#include "newimage/newimageall.h"
#include "newimage/fmribmain.h"

using namespace NEWIMAGE;

void print_usage(const string& progname) {
  cout << "Usage: " << progname << " <input> <a> <b> <c> [output]" << endl;
  cout << endl;
  cout << "  where a,b,c represent the new x,y,z axes in terms of the" << endl;
  cout << "  old axes.  They can take values of -x,x,y,-y,z,-z" << endl;
  cout << "  e.g.  " << progname << " invol y x -z outvol" << endl;
}


template <class T>
int fmrib_main(int argc,char *argv[])
{
  string newx=argv[2], newy=argv[3], newz=argv[4];
  string inname=argv[1];
  string outname="";
  bool showmat=false;
  if (argc==6) {
    outname=argv[5];
    showmat=false;
  } else {
    showmat=true;
  }

  volumeinfo volinfo;
  volume4D<T> invol;
  read_volume4D(invol,inname,volinfo);

  Matrix affmat;
  affmat = invol.swapmat(newx,newy,newz);

  if (showmat) {
    cout << affmat << endl;
  }

  if (affmat.Determinant()<0.0) {
    cerr << "WARNING:: Flipping Left/Right orientation (as det < 0)" << endl;
  }
  
  invol.swapdimensions(newx,newy,newz);

  int retval=0;
  if (outname!="") {
    retval = save_volume4D(invol,outname,volinfo);
  }
  return retval;
}

  
int main(int argc,char *argv[])
{
  string progname=argv[0];
  if (argc<5) { 
    print_usage(progname);
    return -1; 
  }
  
  string inname = argv[1];
  // call the templated main
  return call_fmrib_main(dtype(inname),argc,argv);
}
