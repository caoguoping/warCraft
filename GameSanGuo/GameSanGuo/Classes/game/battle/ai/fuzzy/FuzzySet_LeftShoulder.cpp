#include "FuzzySet_LeftShoulder.h"
#include <cassert>


double FuzzySet_LeftShoulder::CalculateDOM(double val)const
{
 
  if ( (isEqual(m_dRightOffset, 0.0) && (isEqual(m_dPeakPoint, val))) ||
       (isEqual(m_dLeftOffset, 0.0) && (isEqual(m_dPeakPoint, val))) )
  {
    return 1.0;
  }

  
  else if ( (val >= m_dPeakPoint) && (val < (m_dPeakPoint + m_dRightOffset)) )
  {
    double grad = 1.0 / -m_dRightOffset;

    return grad * (val - m_dPeakPoint) + 1.0;
  }

 
  else if ( (val < m_dPeakPoint) && (val >= m_dPeakPoint-m_dLeftOffset) )
  {
    return 1.0;
  }

 
  else
  {
    return 0.0;
  }

}