/*==========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkCovariantVector.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef __itkCovariantVector_h
#define __itkCovariantVector_h


#include "itkArray.h"
#include "vnl/vnl_vector_ref.h"
#include "itkIndent.h"


namespace itk
{

/** \class CovariantVector
 * \brief A templated class holding a n-Dimensional covariant vector.
 * 
 * CovariantVector is a templated class that holds a single vector (i.e., an array
 * of values).  CovariantVector can be used as the data type held at each pixel in
 * an Image or at each vertex of an Mesh. The template parameter T can
 * be any data type that behaves like a primitive (or atomic) data type (int,
 * short, float, complex).  The TCovariantVectorDimension defines the number of
 * components in the vector array. 
 *
 * CovariantVector is not a dynamically extendible array like std::vector. It is
 * intended to be used like a mathematical vector.
 *
 * If you wish a simpler pixel types, you can use Scalar, which represents
 * a single data value at a pixel. There is also the more complex type
 * ScalarCovariantVector, which supports (for a given pixel) a single scalar value
 * plus an array of vector values. (The scalar and vectors can be of
 * different data type.)
 * 
 * CovariantVector is the type that should be used for representing normals
 * to surfaces and gradients of functions. AffineTransform transform
 * covariant vectors different than vectors.
 *
 *
 * \ingroup Geometry
 * \ingroup DataRepresentation
 * 
 * \sa Image
 * \sa Mesh
 * \sa Point
 * \sa CovariantCovariantVector
 * \sa Matrix
 *
 */

template<class T, unsigned int TCovariantVectorDimension=3>
class CovariantVector : public Array<T,TCovariantVectorDimension> {
 public:
  /**
   * Standard "Self" typedef.
   */
  typedef CovariantVector  Self;
  
   
  /**
   * Standard "Superclass" typedef.
   */
  typedef Array<T,TCovariantVectorDimension>  Superclass;


  
  /**
   * ValueType can be used to declare a variable that is the same type
   * as a data element held in an CovariantVector.  
   */
  typedef T ValueType;

  /**
   * Dimension of the Space
   */
  enum { CovariantVectorDimension = TCovariantVectorDimension };

  typedef Self CovariantVectorType;
  
  /**
   * The Array type from which this CovariantVector is derived.
   */
  typedef Array<T, TCovariantVectorDimension>                BaseArray;
  typedef typename BaseArray::ArrayCommaListCopier  ArrayCommaListCopier;
  
  /**
   * Get the dimension (size) of the vector.
   */
  static unsigned int GetCovariantVectorDimension() 
    { return TCovariantVectorDimension; }  

  /**
   * Set a vnl_vector_ref referencing the same memory block
   */
  void Set_vnl_vector( const vnl_vector<T> & );


  /**
   * Get a vnl_vector_ref referencing the same memory block
   */
  vnl_vector_ref<T> Get_vnl_vector( void );


  /**
   * Default constructor has nothing to do.
   */
  CovariantVector() {}

  /*@{
   * Pass-through constructor for the Array base class.
   */
  CovariantVector(const Self& r): BaseArray(r) {}
  CovariantVector(const typename BaseArray::Reference& r): BaseArray(r) {}
  CovariantVector(const typename BaseArray::ConstReference& r): BaseArray(r) {}
  CovariantVector(const ValueType r[CovariantVectorDimension]): BaseArray(r) {}  
  //@}
  
  /*@{
   * Pass-through assignment operator for the Array base class.
   */
  CovariantVector& operator= (const Self& r);
  CovariantVector& operator= (const typename BaseArray::Reference& r);
  CovariantVector& operator= (const typename BaseArray::ConstReference& r);
  CovariantVector& operator= (const ValueType r[CovariantVectorDimension]);
  ArrayCommaListCopier operator= (const ValueType& r);
  //@}
  
  /**
   * Scalar operator*=.  Scales elements by a scalar.
   */
  const Self& operator*=(const ValueType &value);


  /**
   * Scalar operator/=.  Scales (divides) elements by a scalar.
   */
  const Self& operator/=(const ValueType &value);


  /**
   * CovariantVector operator+=.  Adds a vectors to the current vector.
   */
  const Self& operator+=(const Self &vec);


  /**
   * CovariantVector operator-=.  Subtracts a vector from a current vector.
   */
  const Self& operator-=(const Self &vec);


  /**
   * CovariantVector negation.  Negate all the elements of a vector. Return a new vector
   */
  Self operator-() const;
  

  /**
   * CovariantVector addition. Add two vectors. Return a new vector.
   */
  Self operator+(const Self &vec) const;
  

   /**
   * CovariantVector subtraction. Subtract two vectors. Return a new vector.
   */
  Self operator-(const Self &vec) const;
  

  /**
   * Scalar operator*. Scale the elements of a vector by a scalar.
   * Return a new vector.
   */
  Self operator*(const ValueType& val) const;
  

  /**
   * Scalar operator/. Scale (divide) the elements of a vector by a scalar.
   * Return a new vector.
   */
  Self operator/(const ValueType& val) const;


  /**
   * Returns the Euclidean Norm of the vector 
   */
  ValueType GetNorm( void ) const;
  

  /**
   * Returns vector's Squared Euclidean Norm 
   */
  ValueType GetSquaredNorm( void ) const;


  /**
   * Print content
   */
  void PrintSelf(std::ostream& os, Indent indent) const;


 
};

  

template< class T, unsigned int TCovariantVectorDimension >  
ITK_EXPORT std::ostream& operator<<(std::ostream& os, 
          const CovariantVector<T,TCovariantVectorDimension> & v); 

template< class T, unsigned int TCovariantVectorDimension >  
ITK_EXPORT std::istream& operator>>(std::istream& is, 
          CovariantVector<T,TCovariantVectorDimension> & v); 

} // end namespace itk
  

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkCovariantVector.txx"
#endif


#endif 
