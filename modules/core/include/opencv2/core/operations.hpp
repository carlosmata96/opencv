/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#ifndef __OPENCV_CORE_OPERATIONS_HPP__
#define __OPENCV_CORE_OPERATIONS_HPP__

#ifndef SKIP_INCLUDES
  #include <string.h>
  #include <limits.h>
#endif // SKIP_INCLUDES


#ifdef __cplusplus

#include <limits>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4127) //conditional expression is constant
#endif

//////////////// static assert /////////////////

#define CVAUX_CONCAT_EXP(a, b) a##b
#define CVAUX_CONCAT(a, b) CVAUX_CONCAT_EXP(a,b)

#ifdef __cplusplus
#  if defined(__clang__)
#    ifndef __has_extension
#      define __has_extension __has_feature /* compatibility, for older versions of clang */
#    endif
#    if __has_extension(cxx_static_assert)
#      define CV_StaticAssert(condition, reason)    static_assert((condition), reason " " #condition)
#    endif
#  elif defined(__GNUC__)
#    if (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#      define CV_StaticAssert(condition, reason)    static_assert((condition), reason " " #condition)
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1600 /* MSVC 10 */
#      define CV_StaticAssert(condition, reason)    static_assert((condition), reason " " #condition)
#    endif
#  endif
#  ifndef CV_StaticAssert
#    if defined(__GNUC__) && (__GNUC__ > 3) && (__GNUC_MINOR__ > 2)
#      define CV_StaticAssert(condition, reason) ({ extern int __attribute__((error("CV_StaticAssert: " reason " " #condition))) CV_StaticAssert(); ((condition) ? 0 : CV_StaticAssert()); })
#    else
       namespace cv {
         template <bool x> struct CV_StaticAssert_failed;
         template <> struct CV_StaticAssert_failed<true> { enum { val = 1 }; };
         template<int x> struct CV_StaticAssert_test{};
       }
#      define CV_StaticAssert(condition, reason)\
         typedef cv::CV_StaticAssert_test< sizeof(cv::CV_StaticAssert_failed< static_cast<bool>(condition) >) > CVAUX_CONCAT(CV_StaticAssert_failed_at_, __LINE__)
#    endif
#  endif
#endif

namespace cv
{

inline int fast_abs(uchar v) { return v; }
inline int fast_abs(schar v) { return std::abs((int)v); }
inline int fast_abs(ushort v) { return v; }
inline int fast_abs(short v) { return std::abs((int)v); }
inline int fast_abs(int v) { return std::abs(v); }
inline float fast_abs(float v) { return std::abs(v); }
inline double fast_abs(double v) { return std::abs(v); }

//////////////////////////////// Matx /////////////////////////////////


template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx()
{
    for(int i = 0; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0)
{
    val[0] = v0;
    for(int i = 1; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1)
{
    CV_StaticAssert(channels >= 2, "Matx should have at least 2 elaments.");
    val[0] = v0; val[1] = v1;
    for(int i = 2; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2)
{
    CV_StaticAssert(channels >= 3, "Matx should have at least 3 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2;
    for(int i = 3; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3)
{
    CV_StaticAssert(channels >= 4, "Matx should have at least 4 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    for(int i = 4; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3, _Tp v4)
{
    CV_StaticAssert(channels >= 5, "Matx should have at least 5 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3; val[4] = v4;
    for(int i = 5; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5)
{
    CV_StaticAssert(channels >= 6, "Matx should have at least 6 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5;
    for(int i = 6; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6)
{
    CV_StaticAssert(channels >= 7, "Matx should have at least 7 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5; val[6] = v6;
    for(int i = 7; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6, _Tp v7)
{
    CV_StaticAssert(channels >= 8, "Matx should have at least 8 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5; val[6] = v6; val[7] = v7;
    for(int i = 8; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6, _Tp v7,
                                                        _Tp v8)
{
    CV_StaticAssert(channels >= 9, "Matx should have at least 9 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5; val[6] = v6; val[7] = v7;
    val[8] = v8;
    for(int i = 9; i < channels; i++) val[i] = _Tp(0);
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6, _Tp v7,
                                                        _Tp v8, _Tp v9)
{
    CV_StaticAssert(channels >= 10, "Matx should have at least 10 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5; val[6] = v6; val[7] = v7;
    val[8] = v8; val[9] = v9;
    for(int i = 10; i < channels; i++) val[i] = _Tp(0);
}


template<typename _Tp, int m, int n>
inline Matx<_Tp,m,n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                            _Tp v4, _Tp v5, _Tp v6, _Tp v7,
                            _Tp v8, _Tp v9, _Tp v10, _Tp v11)
{
    CV_StaticAssert(channels == 12, "Matx should have at least 12 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5; val[6] = v6; val[7] = v7;
    val[8] = v8; val[9] = v9; val[10] = v10; val[11] = v11;
}

template<typename _Tp, int m, int n>
inline Matx<_Tp,m,n>::Matx(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                           _Tp v4, _Tp v5, _Tp v6, _Tp v7,
                           _Tp v8, _Tp v9, _Tp v10, _Tp v11,
                           _Tp v12, _Tp v13, _Tp v14, _Tp v15)
{
    CV_StaticAssert(channels == 16, "Matx should have at least 16 elaments.");
    val[0] = v0; val[1] = v1; val[2] = v2; val[3] = v3;
    val[4] = v4; val[5] = v5; val[6] = v6; val[7] = v7;
    val[8] = v8; val[9] = v9; val[10] = v10; val[11] = v11;
    val[12] = v12; val[13] = v13; val[14] = v14; val[15] = v15;
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n>::Matx(const _Tp* values)
{
    for( int i = 0; i < channels; i++ ) val[i] = values[i];
}

template<typename _Tp, int m, int n> inline Matx<_Tp, m, n> Matx<_Tp, m, n>::all(_Tp alpha)
{
    Matx<_Tp, m, n> M;
    for( int i = 0; i < m*n; i++ ) M.val[i] = alpha;
    return M;
}

template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n> Matx<_Tp,m,n>::zeros()
{
    return all(0);
}

template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n> Matx<_Tp,m,n>::ones()
{
    return all(1);
}

template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n> Matx<_Tp,m,n>::eye()
{
    Matx<_Tp,m,n> M;
    for(int i = 0; i < MIN(m,n); i++)
        M(i,i) = 1;
    return M;
}

template<typename _Tp, int m, int n> inline _Tp Matx<_Tp, m, n>::dot(const Matx<_Tp, m, n>& M) const
{
    _Tp s = 0;
    for( int i = 0; i < m*n; i++ ) s += val[i]*M.val[i];
    return s;
}


template<typename _Tp, int m, int n> inline double Matx<_Tp, m, n>::ddot(const Matx<_Tp, m, n>& M) const
{
    double s = 0;
    for( int i = 0; i < m*n; i++ ) s += (double)val[i]*M.val[i];
    return s;
}



template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n> Matx<_Tp,m,n>::diag(const typename Matx<_Tp,m,n>::diag_type& d)
{
    Matx<_Tp,m,n> M;
    for(int i = 0; i < MIN(m,n); i++)
        M(i,i) = d(i, 0);
    return M;
}

template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n> Matx<_Tp,m,n>::randu(_Tp a, _Tp b)
{
    Matx<_Tp,m,n> M;
    Mat matM(M, false);
    cv::randu(matM, Scalar(a), Scalar(b));
    return M;
}

template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n> Matx<_Tp,m,n>::randn(_Tp a, _Tp b)
{
    Matx<_Tp,m,n> M;
    Mat matM(M, false);
    cv::randn(matM, Scalar(a), Scalar(b));
    return M;
}

template<typename _Tp, int m, int n> template<typename T2>
inline Matx<_Tp, m, n>::operator Matx<T2, m, n>() const
{
    Matx<T2, m, n> M;
    for( int i = 0; i < m*n; i++ ) M.val[i] = saturate_cast<T2>(val[i]);
    return M;
}


template<typename _Tp, int m, int n> template<int m1, int n1> inline
Matx<_Tp, m1, n1> Matx<_Tp, m, n>::reshape() const
{
    CV_DbgAssert(m1*n1 == m*n);
    return (const Matx<_Tp, m1, n1>&)*this;
}


template<typename _Tp, int m, int n>
template<int m1, int n1> inline
Matx<_Tp, m1, n1> Matx<_Tp, m, n>::get_minor(int i, int j) const
{
    CV_DbgAssert(0 <= i && i+m1 <= m && 0 <= j && j+n1 <= n);
    Matx<_Tp, m1, n1> s;
    for( int di = 0; di < m1; di++ )
        for( int dj = 0; dj < n1; dj++ )
            s(di, dj) = (*this)(i+di, j+dj);
    return s;
}


template<typename _Tp, int m, int n> inline
Matx<_Tp, 1, n> Matx<_Tp, m, n>::row(int i) const
{
    CV_DbgAssert((unsigned)i < (unsigned)m);
    return Matx<_Tp, 1, n>(&val[i*n]);
}


template<typename _Tp, int m, int n> inline
Matx<_Tp, m, 1> Matx<_Tp, m, n>::col(int j) const
{
    CV_DbgAssert((unsigned)j < (unsigned)n);
    Matx<_Tp, m, 1> v;
    for( int i = 0; i < m; i++ )
        v.val[i] = val[i*n + j];
    return v;
}


template<typename _Tp, int m, int n> inline
typename Matx<_Tp, m, n>::diag_type Matx<_Tp, m, n>::diag() const
{
    diag_type d;
    for( int i = 0; i < MIN(m, n); i++ )
        d.val[i] = val[i*n + i];
    return d;
}


template<typename _Tp, int m, int n> inline
const _Tp& Matx<_Tp, m, n>::operator ()(int i, int j) const
{
    CV_DbgAssert( (unsigned)i < (unsigned)m && (unsigned)j < (unsigned)n );
    return this->val[i*n + j];
}


template<typename _Tp, int m, int n> inline
_Tp& Matx<_Tp, m, n>::operator ()(int i, int j)
{
    CV_DbgAssert( (unsigned)i < (unsigned)m && (unsigned)j < (unsigned)n );
    return val[i*n + j];
}


template<typename _Tp, int m, int n> inline
const _Tp& Matx<_Tp, m, n>::operator ()(int i) const
{
    CV_DbgAssert( (m == 1 || n == 1) && (unsigned)i < (unsigned)(m+n-1) );
    return val[i];
}


template<typename _Tp, int m, int n> inline
_Tp& Matx<_Tp, m, n>::operator ()(int i)
{
    CV_DbgAssert( (m == 1 || n == 1) && (unsigned)i < (unsigned)(m+n-1) );
    return val[i];
}


template<typename _Tp1, typename _Tp2, int m, int n> static inline
Matx<_Tp1, m, n>& operator += (Matx<_Tp1, m, n>& a, const Matx<_Tp2, m, n>& b)
{
    for( int i = 0; i < m*n; i++ )
        a.val[i] = saturate_cast<_Tp1>(a.val[i] + b.val[i]);
    return a;
}


template<typename _Tp1, typename _Tp2, int m, int n> static inline
Matx<_Tp1, m, n>& operator -= (Matx<_Tp1, m, n>& a, const Matx<_Tp2, m, n>& b)
{
    for( int i = 0; i < m*n; i++ )
        a.val[i] = saturate_cast<_Tp1>(a.val[i] - b.val[i]);
    return a;
}


template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n>::Matx(const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b, Matx_AddOp)
{
    for( int i = 0; i < m*n; i++ )
        val[i] = saturate_cast<_Tp>(a.val[i] + b.val[i]);
}


template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n>::Matx(const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b, Matx_SubOp)
{
    for( int i = 0; i < m*n; i++ )
        val[i] = saturate_cast<_Tp>(a.val[i] - b.val[i]);
}


template<typename _Tp, int m, int n> template<typename _T2> inline
Matx<_Tp,m,n>::Matx(const Matx<_Tp, m, n>& a, _T2 alpha, Matx_ScaleOp)
{
    for( int i = 0; i < m*n; i++ )
        val[i] = saturate_cast<_Tp>(a.val[i] * alpha);
}


template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n>::Matx(const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b, Matx_MulOp)
{
    for( int i = 0; i < m*n; i++ )
        val[i] = saturate_cast<_Tp>(a.val[i] * b.val[i]);
}


template<typename _Tp, int m, int n> template<int l> inline
Matx<_Tp,m,n>::Matx(const Matx<_Tp, m, l>& a, const Matx<_Tp, l, n>& b, Matx_MatMulOp)
{
    for( int i = 0; i < m; i++ )
        for( int j = 0; j < n; j++ )
        {
            _Tp s = 0;
            for( int k = 0; k < l; k++ )
                s += a(i, k) * b(k, j);
            val[i*n + j] = s;
        }
}


template<typename _Tp, int m, int n> inline
Matx<_Tp,m,n>::Matx(const Matx<_Tp, n, m>& a, Matx_TOp)
{
    for( int i = 0; i < m; i++ )
        for( int j = 0; j < n; j++ )
            val[i*n + j] = a(j, i);
}


template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator + (const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b)
{
    return Matx<_Tp, m, n>(a, b, Matx_AddOp());
}


template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator - (const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b)
{
    return Matx<_Tp, m, n>(a, b, Matx_SubOp());
}


template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n>& operator *= (Matx<_Tp, m, n>& a, int alpha)
{
    for( int i = 0; i < m*n; i++ )
        a.val[i] = saturate_cast<_Tp>(a.val[i] * alpha);
    return a;
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n>& operator *= (Matx<_Tp, m, n>& a, float alpha)
{
    for( int i = 0; i < m*n; i++ )
        a.val[i] = saturate_cast<_Tp>(a.val[i] * alpha);
    return a;
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n>& operator *= (Matx<_Tp, m, n>& a, double alpha)
{
    for( int i = 0; i < m*n; i++ )
        a.val[i] = saturate_cast<_Tp>(a.val[i] * alpha);
    return a;
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator * (const Matx<_Tp, m, n>& a, int alpha)
{
    return Matx<_Tp, m, n>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator * (const Matx<_Tp, m, n>& a, float alpha)
{
    return Matx<_Tp, m, n>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator * (const Matx<_Tp, m, n>& a, double alpha)
{
    return Matx<_Tp, m, n>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator * (int alpha, const Matx<_Tp, m, n>& a)
{
    return Matx<_Tp, m, n>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator * (float alpha, const Matx<_Tp, m, n>& a)
{
    return Matx<_Tp, m, n>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator * (double alpha, const Matx<_Tp, m, n>& a)
{
    return Matx<_Tp, m, n>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int m, int n> static inline
Matx<_Tp, m, n> operator - (const Matx<_Tp, m, n>& a)
{
    return Matx<_Tp, m, n>(a, -1, Matx_ScaleOp());
}


template<typename _Tp, int m, int n, int l> static inline
Matx<_Tp, m, n> operator * (const Matx<_Tp, m, l>& a, const Matx<_Tp, l, n>& b)
{
    return Matx<_Tp, m, n>(a, b, Matx_MatMulOp());
}


template<typename _Tp, int m, int n> static inline
Vec<_Tp, m> operator * (const Matx<_Tp, m, n>& a, const Vec<_Tp, n>& b)
{
    Matx<_Tp, m, 1> c(a, b, Matx_MatMulOp());
    return reinterpret_cast<const Vec<_Tp, m>&>(c);
}


template<typename _Tp> static inline
Point_<_Tp> operator * (const Matx<_Tp, 2, 2>& a, const Point_<_Tp>& b)
{
    Matx<_Tp, 2, 1> tmp = a*Vec<_Tp,2>(b.x, b.y);
    return Point_<_Tp>(tmp.val[0], tmp.val[1]);
}


template<typename _Tp> static inline
Point3_<_Tp> operator * (const Matx<_Tp, 3, 3>& a, const Point3_<_Tp>& b)
{
    Matx<_Tp, 3, 1> tmp = a*Vec<_Tp,3>(b.x, b.y, b.z);
    return Point3_<_Tp>(tmp.val[0], tmp.val[1], tmp.val[2]);
}


template<typename _Tp> static inline
Point3_<_Tp> operator * (const Matx<_Tp, 3, 3>& a, const Point_<_Tp>& b)
{
    Matx<_Tp, 3, 1> tmp = a*Vec<_Tp,3>(b.x, b.y, 1);
    return Point3_<_Tp>(tmp.val[0], tmp.val[1], tmp.val[2]);
}


template<typename _Tp> static inline
Matx<_Tp, 4, 1> operator * (const Matx<_Tp, 4, 4>& a, const Point3_<_Tp>& b)
{
    return a*Matx<_Tp, 4, 1>(b.x, b.y, b.z, 1);
}


template<typename _Tp> static inline
Scalar operator * (const Matx<_Tp, 4, 4>& a, const Scalar& b)
{
    Matx<double, 4, 1> c(Matx<double, 4, 4>(a), b, Matx_MatMulOp());
    return reinterpret_cast<const Scalar&>(c);
}


static inline
Scalar operator * (const Matx<double, 4, 4>& a, const Scalar& b)
{
    Matx<double, 4, 1> c(a, b, Matx_MatMulOp());
    return reinterpret_cast<const Scalar&>(c);
}


template<typename _Tp, int m, int n> inline
Matx<_Tp, m, n> Matx<_Tp, m, n>::mul(const Matx<_Tp, m, n>& a) const
{
    return Matx<_Tp, m, n>(*this, a, Matx_MulOp());
}


CV_EXPORTS int LU(float* A, size_t astep, int m, float* b, size_t bstep, int n);
CV_EXPORTS int LU(double* A, size_t astep, int m, double* b, size_t bstep, int n);
CV_EXPORTS bool Cholesky(float* A, size_t astep, int m, float* b, size_t bstep, int n);
CV_EXPORTS bool Cholesky(double* A, size_t astep, int m, double* b, size_t bstep, int n);


template<typename _Tp, int m> struct CV_EXPORTS Matx_DetOp
{
    double operator ()(const Matx<_Tp, m, m>& a) const
    {
        Matx<_Tp, m, m> temp = a;
        double p = LU(temp.val, m*sizeof(_Tp), m, 0, 0, 0);
        if( p == 0 )
            return p;
        for( int i = 0; i < m; i++ )
            p *= temp(i, i);
        return 1./p;
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_DetOp<_Tp, 1>
{
    double operator ()(const Matx<_Tp, 1, 1>& a) const
    {
        return a(0,0);
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_DetOp<_Tp, 2>
{
    double operator ()(const Matx<_Tp, 2, 2>& a) const
    {
        return a(0,0)*a(1,1) - a(0,1)*a(1,0);
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_DetOp<_Tp, 3>
{
    double operator ()(const Matx<_Tp, 3, 3>& a) const
    {
        return a(0,0)*(a(1,1)*a(2,2) - a(2,1)*a(1,2)) -
            a(0,1)*(a(1,0)*a(2,2) - a(2,0)*a(1,2)) +
            a(0,2)*(a(1,0)*a(2,1) - a(2,0)*a(1,1));
    }
};

template<typename _Tp, int m> static inline
double determinant(const Matx<_Tp, m, m>& a)
{
    return Matx_DetOp<_Tp, m>()(a);
}


template<typename _Tp, int m, int n> static inline
double trace(const Matx<_Tp, m, n>& a)
{
    _Tp s = 0;
    for( int i = 0; i < std::min(m, n); i++ )
        s += a(i,i);
    return s;
}


template<typename _Tp, int m, int n> inline
Matx<_Tp, n, m> Matx<_Tp, m, n>::t() const
{
    return Matx<_Tp, n, m>(*this, Matx_TOp());
}


template<typename _Tp, int m> struct CV_EXPORTS Matx_FastInvOp
{
    bool operator()(const Matx<_Tp, m, m>& a, Matx<_Tp, m, m>& b, int method) const
    {
        Matx<_Tp, m, m> temp = a;

        // assume that b is all 0's on input => make it a unity matrix
        for( int i = 0; i < m; i++ )
            b(i, i) = (_Tp)1;

        if( method == DECOMP_CHOLESKY )
            return Cholesky(temp.val, m*sizeof(_Tp), m, b.val, m*sizeof(_Tp), m);

        return LU(temp.val, m*sizeof(_Tp), m, b.val, m*sizeof(_Tp), m) != 0;
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_FastInvOp<_Tp, 2>
{
    bool operator()(const Matx<_Tp, 2, 2>& a, Matx<_Tp, 2, 2>& b, int) const
    {
        _Tp d = determinant(a);
        if( d == 0 )
            return false;
        d = 1/d;
        b(1,1) = a(0,0)*d;
        b(0,0) = a(1,1)*d;
        b(0,1) = -a(0,1)*d;
        b(1,0) = -a(1,0)*d;
        return true;
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_FastInvOp<_Tp, 3>
{
    bool operator()(const Matx<_Tp, 3, 3>& a, Matx<_Tp, 3, 3>& b, int) const
    {
        _Tp d = (_Tp)determinant(a);
        if( d == 0 )
            return false;
        d = 1/d;
        b(0,0) = (a(1,1) * a(2,2) - a(1,2) * a(2,1)) * d;
        b(0,1) = (a(0,2) * a(2,1) - a(0,1) * a(2,2)) * d;
        b(0,2) = (a(0,1) * a(1,2) - a(0,2) * a(1,1)) * d;

        b(1,0) = (a(1,2) * a(2,0) - a(1,0) * a(2,2)) * d;
        b(1,1) = (a(0,0) * a(2,2) - a(0,2) * a(2,0)) * d;
        b(1,2) = (a(0,2) * a(1,0) - a(0,0) * a(1,2)) * d;

        b(2,0) = (a(1,0) * a(2,1) - a(1,1) * a(2,0)) * d;
        b(2,1) = (a(0,1) * a(2,0) - a(0,0) * a(2,1)) * d;
        b(2,2) = (a(0,0) * a(1,1) - a(0,1) * a(1,0)) * d;
        return true;
    }
};


template<typename _Tp, int m, int n> inline
Matx<_Tp, n, m> Matx<_Tp, m, n>::inv(int method) const
{
    Matx<_Tp, n, m> b;
    bool ok;
    if( method == DECOMP_LU || method == DECOMP_CHOLESKY )
        ok = Matx_FastInvOp<_Tp, m>()(*this, b, method);
    else
    {
        Mat A(*this, false), B(b, false);
        ok = (invert(A, B, method) != 0);
    }
    return ok ? b : Matx<_Tp, n, m>::zeros();
}


template<typename _Tp, int m, int n> struct CV_EXPORTS Matx_FastSolveOp
{
    bool operator()(const Matx<_Tp, m, m>& a, const Matx<_Tp, m, n>& b,
                    Matx<_Tp, m, n>& x, int method) const
    {
        Matx<_Tp, m, m> temp = a;
        x = b;
        if( method == DECOMP_CHOLESKY )
            return Cholesky(temp.val, m*sizeof(_Tp), m, x.val, n*sizeof(_Tp), n);

        return LU(temp.val, m*sizeof(_Tp), m, x.val, n*sizeof(_Tp), n) != 0;
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_FastSolveOp<_Tp, 2, 1>
{
    bool operator()(const Matx<_Tp, 2, 2>& a, const Matx<_Tp, 2, 1>& b,
                    Matx<_Tp, 2, 1>& x, int) const
    {
        _Tp d = determinant(a);
        if( d == 0 )
            return false;
        d = 1/d;
        x(0) = (b(0)*a(1,1) - b(1)*a(0,1))*d;
        x(1) = (b(1)*a(0,0) - b(0)*a(1,0))*d;
        return true;
    }
};


template<typename _Tp> struct CV_EXPORTS Matx_FastSolveOp<_Tp, 3, 1>
{
    bool operator()(const Matx<_Tp, 3, 3>& a, const Matx<_Tp, 3, 1>& b,
                    Matx<_Tp, 3, 1>& x, int) const
    {
        _Tp d = (_Tp)determinant(a);
        if( d == 0 )
            return false;
        d = 1/d;
        x(0) = d*(b(0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1)) -
                a(0,1)*(b(1)*a(2,2) - a(1,2)*b(2)) +
                a(0,2)*(b(1)*a(2,1) - a(1,1)*b(2)));

        x(1) = d*(a(0,0)*(b(1)*a(2,2) - a(1,2)*b(2)) -
                b(0)*(a(1,0)*a(2,2) - a(1,2)*a(2,0)) +
                a(0,2)*(a(1,0)*b(2) - b(1)*a(2,0)));

        x(2) = d*(a(0,0)*(a(1,1)*b(2) - b(1)*a(2,1)) -
                a(0,1)*(a(1,0)*b(2) - b(1)*a(2,0)) +
                b(0)*(a(1,0)*a(2,1) - a(1,1)*a(2,0)));
        return true;
    }
};


template<typename _Tp, int m, int n> template<int l> inline
Matx<_Tp, n, l> Matx<_Tp, m, n>::solve(const Matx<_Tp, m, l>& rhs, int method) const
{
    Matx<_Tp, n, l> x;
    bool ok;
    if( method == DECOMP_LU || method == DECOMP_CHOLESKY )
        ok = Matx_FastSolveOp<_Tp, m, l>()(*this, rhs, x, method);
    else
    {
        Mat A(*this, false), B(rhs, false), X(x, false);
        ok = cv::solve(A, B, X, method);
    }

    return ok ? x : Matx<_Tp, n, l>::zeros();
}

template<typename _Tp, int m, int n> inline
Vec<_Tp, n> Matx<_Tp, m, n>::solve(const Vec<_Tp, m>& rhs, int method) const
{
    Matx<_Tp, n, 1> x = solve(reinterpret_cast<const Matx<_Tp, m, 1>&>(rhs), method);
    return reinterpret_cast<Vec<_Tp, n>&>(x);
}

template<typename _Tp, typename _AccTp> static inline
_AccTp normL2Sqr(const _Tp* a, int n)
{
    _AccTp s = 0;
    int i=0;
 #if CV_ENABLE_UNROLLED
    for( ; i <= n - 4; i += 4 )
    {
        _AccTp v0 = a[i], v1 = a[i+1], v2 = a[i+2], v3 = a[i+3];
        s += v0*v0 + v1*v1 + v2*v2 + v3*v3;
    }
#endif
    for( ; i < n; i++ )
    {
        _AccTp v = a[i];
        s += v*v;
    }
    return s;
}


template<typename _Tp, typename _AccTp> static inline
_AccTp normL1(const _Tp* a, int n)
{
    _AccTp s = 0;
    int i = 0;
#if CV_ENABLE_UNROLLED
    for(; i <= n - 4; i += 4 )
    {
        s += (_AccTp)fast_abs(a[i]) + (_AccTp)fast_abs(a[i+1]) +
            (_AccTp)fast_abs(a[i+2]) + (_AccTp)fast_abs(a[i+3]);
    }
#endif
    for( ; i < n; i++ )
        s += fast_abs(a[i]);
    return s;
}


template<typename _Tp, typename _AccTp> static inline
_AccTp normInf(const _Tp* a, int n)
{
    _AccTp s = 0;
    for( int i = 0; i < n; i++ )
        s = std::max(s, (_AccTp)fast_abs(a[i]));
    return s;
}


template<typename _Tp, typename _AccTp> static inline
_AccTp normL2Sqr(const _Tp* a, const _Tp* b, int n)
{
    _AccTp s = 0;
    int i= 0;
#if CV_ENABLE_UNROLLED
    for(; i <= n - 4; i += 4 )
    {
        _AccTp v0 = _AccTp(a[i] - b[i]), v1 = _AccTp(a[i+1] - b[i+1]), v2 = _AccTp(a[i+2] - b[i+2]), v3 = _AccTp(a[i+3] - b[i+3]);
        s += v0*v0 + v1*v1 + v2*v2 + v3*v3;
    }
#endif
    for( ; i < n; i++ )
    {
        _AccTp v = _AccTp(a[i] - b[i]);
        s += v*v;
    }
    return s;
}

CV_EXPORTS float normL2Sqr_(const float* a, const float* b, int n);
CV_EXPORTS float normL1_(const float* a, const float* b, int n);
CV_EXPORTS int normL1_(const uchar* a, const uchar* b, int n);
CV_EXPORTS int normHamming(const uchar* a, const uchar* b, int n);
CV_EXPORTS int normHamming(const uchar* a, const uchar* b, int n, int cellSize);

template<> inline float normL2Sqr(const float* a, const float* b, int n)
{
    if( n >= 8 )
        return normL2Sqr_(a, b, n);
    float s = 0;
    for( int i = 0; i < n; i++ )
    {
        float v = a[i] - b[i];
        s += v*v;
    }
    return s;
}


template<typename _Tp, typename _AccTp> static inline
_AccTp normL1(const _Tp* a, const _Tp* b, int n)
{
    _AccTp s = 0;
    int i= 0;
#if CV_ENABLE_UNROLLED
    for(; i <= n - 4; i += 4 )
    {
        _AccTp v0 = _AccTp(a[i] - b[i]), v1 = _AccTp(a[i+1] - b[i+1]), v2 = _AccTp(a[i+2] - b[i+2]), v3 = _AccTp(a[i+3] - b[i+3]);
        s += std::abs(v0) + std::abs(v1) + std::abs(v2) + std::abs(v3);
    }
#endif
    for( ; i < n; i++ )
    {
        _AccTp v = _AccTp(a[i] - b[i]);
        s += std::abs(v);
    }
    return s;
}

template<> inline float normL1(const float* a, const float* b, int n)
{
    if( n >= 8 )
        return normL1_(a, b, n);
    float s = 0;
    for( int i = 0; i < n; i++ )
    {
        float v = a[i] - b[i];
        s += std::abs(v);
    }
    return s;
}

template<> inline int normL1(const uchar* a, const uchar* b, int n)
{
    return normL1_(a, b, n);
}

template<typename _Tp, typename _AccTp> static inline
_AccTp normInf(const _Tp* a, const _Tp* b, int n)
{
    _AccTp s = 0;
    for( int i = 0; i < n; i++ )
    {
        _AccTp v0 = a[i] - b[i];
        s = std::max(s, std::abs(v0));
    }
    return s;
}


template<typename _Tp, int m, int n> static inline
double norm(const Matx<_Tp, m, n>& M)
{
    return std::sqrt(normL2Sqr<_Tp, double>(M.val, m*n));
}


template<typename _Tp, int m, int n> static inline
double norm(const Matx<_Tp, m, n>& M, int normType)
{
    return normType == NORM_INF ? (double)normInf<_Tp, typename DataType<_Tp>::work_type>(M.val, m*n) :
        normType == NORM_L1 ? (double)normL1<_Tp, typename DataType<_Tp>::work_type>(M.val, m*n) :
        std::sqrt((double)normL2Sqr<_Tp, typename DataType<_Tp>::work_type>(M.val, m*n));
}


template<typename _Tp, int m, int n> static inline
bool operator == (const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b)
{
    for( int i = 0; i < m*n; i++ )
        if( a.val[i] != b.val[i] ) return false;
    return true;
}

template<typename _Tp, int m, int n> static inline
bool operator != (const Matx<_Tp, m, n>& a, const Matx<_Tp, m, n>& b)
{
    return !(a == b);
}


template<typename _Tp, typename _T2, int m, int n> static inline
MatxCommaInitializer<_Tp, m, n> operator << (const Matx<_Tp, m, n>& mtx, _T2 val)
{
    MatxCommaInitializer<_Tp, m, n> commaInitializer((Matx<_Tp, m, n>*)&mtx);
    return (commaInitializer, val);
}

template<typename _Tp, int m, int n> inline
MatxCommaInitializer<_Tp, m, n>::MatxCommaInitializer(Matx<_Tp, m, n>* _mtx)
    : dst(_mtx), idx(0)
{}

template<typename _Tp, int m, int n> template<typename _T2> inline
MatxCommaInitializer<_Tp, m, n>& MatxCommaInitializer<_Tp, m, n>::operator , (_T2 value)
{
    CV_DbgAssert( idx < m*n );
    dst->val[idx++] = saturate_cast<_Tp>(value);
    return *this;
}

template<typename _Tp, int m, int n> inline
Matx<_Tp, m, n> MatxCommaInitializer<_Tp, m, n>::operator *() const
{
    CV_DbgAssert( idx == n*m );
    return *dst;
}

/////////////////////////// short vector (Vec) /////////////////////////////

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec()
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0)
    : Matx<_Tp, cn, 1>(v0)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1)
    : Matx<_Tp, cn, 1>(v0, v1)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2)
    : Matx<_Tp, cn, 1>(v0, v1, v2)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3, _Tp v4)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3, v4)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3, _Tp v4, _Tp v5)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3, v4, v5)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3, v4, v5, v6)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6, _Tp v7)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3, v4, v5, v6, v7)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6, _Tp v7,
                                                        _Tp v8)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3, v4, v5, v6, v7, v8)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3,
                                                        _Tp v4, _Tp v5, _Tp v6, _Tp v7,
                                                        _Tp v8, _Tp v9)
    : Matx<_Tp, cn, 1>(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(const _Tp* values)
    : Matx<_Tp, cn, 1>(values)
{}


template<typename _Tp, int cn> inline Vec<_Tp, cn>::Vec(const Vec<_Tp, cn>& m)
    : Matx<_Tp, cn, 1>(m.val)
{}

template<typename _Tp, int cn> inline
Vec<_Tp, cn>::Vec(const Matx<_Tp, cn, 1>& a, const Matx<_Tp, cn, 1>& b, Matx_AddOp op)
: Matx<_Tp, cn, 1>(a, b, op)
{}

template<typename _Tp, int cn> inline
Vec<_Tp, cn>::Vec(const Matx<_Tp, cn, 1>& a, const Matx<_Tp, cn, 1>& b, Matx_SubOp op)
: Matx<_Tp, cn, 1>(a, b, op)
{}

template<typename _Tp, int cn> template<typename _T2> inline
Vec<_Tp, cn>::Vec(const Matx<_Tp, cn, 1>& a, _T2 alpha, Matx_ScaleOp op)
: Matx<_Tp, cn, 1>(a, alpha, op)
{}

template<typename _Tp, int cn> inline Vec<_Tp, cn> Vec<_Tp, cn>::all(_Tp alpha)
{
    Vec v;
    for( int i = 0; i < cn; i++ ) v.val[i] = alpha;
    return v;
}

template<typename _Tp, int cn> inline Vec<_Tp, cn> Vec<_Tp, cn>::mul(const Vec<_Tp, cn>& v) const
{
    Vec<_Tp, cn> w;
    for( int i = 0; i < cn; i++ ) w.val[i] = saturate_cast<_Tp>(this->val[i]*v.val[i]);
    return w;
}

template<typename _Tp> Vec<_Tp, 2> conjugate(const Vec<_Tp, 2>& v)
{
    return Vec<_Tp, 2>(v[0], -v[1]);
}

template<typename _Tp> Vec<_Tp, 4> conjugate(const Vec<_Tp, 4>& v)
{
    return Vec<_Tp, 4>(v[0], -v[1], -v[2], -v[3]);
}

template<> inline Vec<float, 2> Vec<float, 2>::conj() const
{
    return conjugate(*this);
}

template<> inline Vec<double, 2> Vec<double, 2>::conj() const
{
    return conjugate(*this);
}

template<> inline Vec<float, 4> Vec<float, 4>::conj() const
{
    return conjugate(*this);
}

template<> inline Vec<double, 4> Vec<double, 4>::conj() const
{
    return conjugate(*this);
}

template<typename _Tp, int cn> inline Vec<_Tp, cn> Vec<_Tp, cn>::cross(const Vec<_Tp, cn>&) const
{
    CV_Error(CV_StsError, "for arbitrary-size vector there is no cross-product defined");
    return Vec<_Tp, cn>();
}

template<typename _Tp, int cn> template<typename T2>
inline Vec<_Tp, cn>::operator Vec<T2, cn>() const
{
    Vec<T2, cn> v;
    for( int i = 0; i < cn; i++ ) v.val[i] = saturate_cast<T2>(this->val[i]);
    return v;
}

template<typename _Tp, int cn> inline Vec<_Tp, cn>::operator CvScalar() const
{
    CvScalar s = {{0,0,0,0}};
    int i;
    for( i = 0; i < std::min(cn, 4); i++ ) s.val[i] = this->val[i];
    for( ; i < 4; i++ ) s.val[i] = 0;
    return s;
}

template<typename _Tp, int cn> inline const _Tp& Vec<_Tp, cn>::operator [](int i) const
{
    CV_DbgAssert( (unsigned)i < (unsigned)cn );
    return this->val[i];
}

template<typename _Tp, int cn> inline _Tp& Vec<_Tp, cn>::operator [](int i)
{
    CV_DbgAssert( (unsigned)i < (unsigned)cn );
    return this->val[i];
}

template<typename _Tp, int cn> inline const _Tp& Vec<_Tp, cn>::operator ()(int i) const
{
    CV_DbgAssert( (unsigned)i < (unsigned)cn );
    return this->val[i];
}

template<typename _Tp, int cn> inline _Tp& Vec<_Tp, cn>::operator ()(int i)
{
    CV_DbgAssert( (unsigned)i < (unsigned)cn );
    return this->val[i];
}

template<typename _Tp1, typename _Tp2, int cn> static inline Vec<_Tp1, cn>&
operator += (Vec<_Tp1, cn>& a, const Vec<_Tp2, cn>& b)
{
    for( int i = 0; i < cn; i++ )
        a.val[i] = saturate_cast<_Tp1>(a.val[i] + b.val[i]);
    return a;
}

template<typename _Tp1, typename _Tp2, int cn> static inline Vec<_Tp1, cn>&
operator -= (Vec<_Tp1, cn>& a, const Vec<_Tp2, cn>& b)
{
    for( int i = 0; i < cn; i++ )
        a.val[i] = saturate_cast<_Tp1>(a.val[i] - b.val[i]);
    return a;
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator + (const Vec<_Tp, cn>& a, const Vec<_Tp, cn>& b)
{
    return Vec<_Tp, cn>(a, b, Matx_AddOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator - (const Vec<_Tp, cn>& a, const Vec<_Tp, cn>& b)
{
    return Vec<_Tp, cn>(a, b, Matx_SubOp());
}

template<typename _Tp, int cn> static inline
Vec<_Tp, cn>& operator *= (Vec<_Tp, cn>& a, int alpha)
{
    for( int i = 0; i < cn; i++ )
        a[i] = saturate_cast<_Tp>(a[i]*alpha);
    return a;
}

template<typename _Tp, int cn> static inline
Vec<_Tp, cn>& operator *= (Vec<_Tp, cn>& a, float alpha)
{
    for( int i = 0; i < cn; i++ )
        a[i] = saturate_cast<_Tp>(a[i]*alpha);
    return a;
}

template<typename _Tp, int cn> static inline
Vec<_Tp, cn>& operator *= (Vec<_Tp, cn>& a, double alpha)
{
    for( int i = 0; i < cn; i++ )
        a[i] = saturate_cast<_Tp>(a[i]*alpha);
    return a;
}

template<typename _Tp, int cn> static inline
Vec<_Tp, cn>& operator /= (Vec<_Tp, cn>& a, int alpha)
{
    double ialpha = 1./alpha;
    for( int i = 0; i < cn; i++ )
        a[i] = saturate_cast<_Tp>(a[i]*ialpha);
    return a;
}

template<typename _Tp, int cn> static inline
Vec<_Tp, cn>& operator /= (Vec<_Tp, cn>& a, float alpha)
{
    float ialpha = 1.f/alpha;
    for( int i = 0; i < cn; i++ )
        a[i] = saturate_cast<_Tp>(a[i]*ialpha);
    return a;
}

template<typename _Tp, int cn> static inline
Vec<_Tp, cn>& operator /= (Vec<_Tp, cn>& a, double alpha)
{
    double ialpha = 1./alpha;
    for( int i = 0; i < cn; i++ )
        a[i] = saturate_cast<_Tp>(a[i]*ialpha);
    return a;
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator * (const Vec<_Tp, cn>& a, int alpha)
{
    return Vec<_Tp, cn>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator * (int alpha, const Vec<_Tp, cn>& a)
{
    return Vec<_Tp, cn>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator * (const Vec<_Tp, cn>& a, float alpha)
{
    return Vec<_Tp, cn>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator * (float alpha, const Vec<_Tp, cn>& a)
{
    return Vec<_Tp, cn>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator * (const Vec<_Tp, cn>& a, double alpha)
{
    return Vec<_Tp, cn>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator * (double alpha, const Vec<_Tp, cn>& a)
{
    return Vec<_Tp, cn>(a, alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator / (const Vec<_Tp, cn>& a, int alpha)
{
    return Vec<_Tp, cn>(a, 1./alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator / (const Vec<_Tp, cn>& a, float alpha)
{
    return Vec<_Tp, cn>(a, 1.f/alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator / (const Vec<_Tp, cn>& a, double alpha)
{
    return Vec<_Tp, cn>(a, 1./alpha, Matx_ScaleOp());
}

template<typename _Tp, int cn> static inline Vec<_Tp, cn>
operator - (const Vec<_Tp, cn>& a)
{
    Vec<_Tp,cn> t;
    for( int i = 0; i < cn; i++ ) t.val[i] = saturate_cast<_Tp>(-a.val[i]);
    return t;
}

template<typename _Tp> inline Vec<_Tp, 4> operator * (const Vec<_Tp, 4>& v1, const Vec<_Tp, 4>& v2)
{
    return Vec<_Tp, 4>(saturate_cast<_Tp>(v1[0]*v2[0] - v1[1]*v2[1] - v1[2]*v2[2] - v1[3]*v2[3]),
                       saturate_cast<_Tp>(v1[0]*v2[1] + v1[1]*v2[0] + v1[2]*v2[3] - v1[3]*v2[2]),
                       saturate_cast<_Tp>(v1[0]*v2[2] - v1[1]*v2[3] + v1[2]*v2[0] + v1[3]*v2[1]),
                       saturate_cast<_Tp>(v1[0]*v2[3] + v1[1]*v2[2] - v1[2]*v2[1] + v1[3]*v2[0]));
}

template<typename _Tp> inline Vec<_Tp, 4>& operator *= (Vec<_Tp, 4>& v1, const Vec<_Tp, 4>& v2)
{
    v1 = v1 * v2;
    return v1;
}

template<> inline Vec<float, 3> Vec<float, 3>::cross(const Vec<float, 3>& v) const
{
    return Vec<float,3>(val[1]*v.val[2] - val[2]*v.val[1],
                     val[2]*v.val[0] - val[0]*v.val[2],
                     val[0]*v.val[1] - val[1]*v.val[0]);
}

template<> inline Vec<double, 3> Vec<double, 3>::cross(const Vec<double, 3>& v) const
{
    return Vec<double,3>(val[1]*v.val[2] - val[2]*v.val[1],
                     val[2]*v.val[0] - val[0]*v.val[2],
                     val[0]*v.val[1] - val[1]*v.val[0]);
}

template<typename _Tp, int cn> inline Vec<_Tp, cn> normalize(const Vec<_Tp, cn>& v)
{
    double nv = norm(v);
    return v * (nv ? 1./nv : 0.);
}

template<typename _Tp, typename _T2, int cn> static inline
VecCommaInitializer<_Tp, cn> operator << (const Vec<_Tp, cn>& vec, _T2 val)
{
    VecCommaInitializer<_Tp, cn> commaInitializer((Vec<_Tp, cn>*)&vec);
    return (commaInitializer, val);
}

template<typename _Tp, int cn> inline
VecCommaInitializer<_Tp, cn>::VecCommaInitializer(Vec<_Tp, cn>* _vec)
    : MatxCommaInitializer<_Tp, cn, 1>(_vec)
{}

template<typename _Tp, int cn> template<typename _T2> inline
VecCommaInitializer<_Tp, cn>& VecCommaInitializer<_Tp, cn>::operator , (_T2 value)
{
    CV_DbgAssert( this->idx < cn );
    this->dst->val[this->idx++] = saturate_cast<_Tp>(value);
    return *this;
}

template<typename _Tp, int cn> inline
Vec<_Tp, cn> VecCommaInitializer<_Tp, cn>::operator *() const
{
    CV_DbgAssert( this->idx == cn );
    return *this->dst;
}

//////////////////////////////// Complex //////////////////////////////

template<typename _Tp> inline Complex<_Tp>::Complex() : re(0), im(0) {}
template<typename _Tp> inline Complex<_Tp>::Complex( _Tp _re, _Tp _im ) : re(_re), im(_im) {}
template<typename _Tp> template<typename T2> inline Complex<_Tp>::operator Complex<T2>() const
{ return Complex<T2>(saturate_cast<T2>(re), saturate_cast<T2>(im)); }
template<typename _Tp> inline Complex<_Tp> Complex<_Tp>::conj() const
{ return Complex<_Tp>(re, -im); }

template<typename _Tp> static inline
bool operator == (const Complex<_Tp>& a, const Complex<_Tp>& b)
{ return a.re == b.re && a.im == b.im; }

template<typename _Tp> static inline
bool operator != (const Complex<_Tp>& a, const Complex<_Tp>& b)
{ return a.re != b.re || a.im != b.im; }

template<typename _Tp> static inline
Complex<_Tp> operator + (const Complex<_Tp>& a, const Complex<_Tp>& b)
{ return Complex<_Tp>( a.re + b.re, a.im + b.im ); }

template<typename _Tp> static inline
Complex<_Tp>& operator += (Complex<_Tp>& a, const Complex<_Tp>& b)
{ a.re += b.re; a.im += b.im; return a; }

template<typename _Tp> static inline
Complex<_Tp> operator - (const Complex<_Tp>& a, const Complex<_Tp>& b)
{ return Complex<_Tp>( a.re - b.re, a.im - b.im ); }

template<typename _Tp> static inline
Complex<_Tp>& operator -= (Complex<_Tp>& a, const Complex<_Tp>& b)
{ a.re -= b.re; a.im -= b.im; return a; }

template<typename _Tp> static inline
Complex<_Tp> operator - (const Complex<_Tp>& a)
{ return Complex<_Tp>(-a.re, -a.im); }

template<typename _Tp> static inline
Complex<_Tp> operator * (const Complex<_Tp>& a, const Complex<_Tp>& b)
{ return Complex<_Tp>( a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re ); }

template<typename _Tp> static inline
Complex<_Tp> operator * (const Complex<_Tp>& a, _Tp b)
{ return Complex<_Tp>( a.re*b, a.im*b ); }

template<typename _Tp> static inline
Complex<_Tp> operator * (_Tp b, const Complex<_Tp>& a)
{ return Complex<_Tp>( a.re*b, a.im*b ); }

template<typename _Tp> static inline
Complex<_Tp> operator + (const Complex<_Tp>& a, _Tp b)
{ return Complex<_Tp>( a.re + b, a.im ); }

template<typename _Tp> static inline
Complex<_Tp> operator - (const Complex<_Tp>& a, _Tp b)
{ return Complex<_Tp>( a.re - b, a.im ); }

template<typename _Tp> static inline
Complex<_Tp> operator + (_Tp b, const Complex<_Tp>& a)
{ return Complex<_Tp>( a.re + b, a.im ); }

template<typename _Tp> static inline
Complex<_Tp> operator - (_Tp b, const Complex<_Tp>& a)
{ return Complex<_Tp>( b - a.re, -a.im ); }

template<typename _Tp> static inline
Complex<_Tp>& operator += (Complex<_Tp>& a, _Tp b)
{ a.re += b; return a; }

template<typename _Tp> static inline
Complex<_Tp>& operator -= (Complex<_Tp>& a, _Tp b)
{ a.re -= b; return a; }

template<typename _Tp> static inline
Complex<_Tp>& operator *= (Complex<_Tp>& a, _Tp b)
{ a.re *= b; a.im *= b; return a; }

template<typename _Tp> static inline
double abs(const Complex<_Tp>& a)
{ return std::sqrt( (double)a.re*a.re + (double)a.im*a.im); }

template<typename _Tp> static inline
Complex<_Tp> operator / (const Complex<_Tp>& a, const Complex<_Tp>& b)
{
    double t = 1./((double)b.re*b.re + (double)b.im*b.im);
    return Complex<_Tp>( (_Tp)((a.re*b.re + a.im*b.im)*t),
                        (_Tp)((-a.re*b.im + a.im*b.re)*t) );
}

template<typename _Tp> static inline
Complex<_Tp>& operator /= (Complex<_Tp>& a, const Complex<_Tp>& b)
{
    return (a = a / b);
}

template<typename _Tp> static inline
Complex<_Tp> operator / (const Complex<_Tp>& a, _Tp b)
{
    _Tp t = (_Tp)1/b;
    return Complex<_Tp>( a.re*t, a.im*t );
}

template<typename _Tp> static inline
Complex<_Tp> operator / (_Tp b, const Complex<_Tp>& a)
{
    return Complex<_Tp>(b)/a;
}

template<typename _Tp> static inline
Complex<_Tp> operator /= (const Complex<_Tp>& a, _Tp b)
{
    _Tp t = (_Tp)1/b;
    a.re *= t; a.im *= t; return a;
}

//////////////////////////////// 2D Point ////////////////////////////////

template<typename _Tp> inline Point_<_Tp>::Point_() : x(0), y(0) {}
template<typename _Tp> inline Point_<_Tp>::Point_(_Tp _x, _Tp _y) : x(_x), y(_y) {}
template<typename _Tp> inline Point_<_Tp>::Point_(const Point_& pt) : x(pt.x), y(pt.y) {}
template<typename _Tp> inline Point_<_Tp>::Point_(const Size_<_Tp>& sz) : x(sz.width), y(sz.height) {}
template<typename _Tp> inline Point_<_Tp>::Point_(const Vec<_Tp,2>& v) : x(v[0]), y(v[1]) {}
template<typename _Tp> inline Point_<_Tp>& Point_<_Tp>::operator = (const Point_& pt)
{ x = pt.x; y = pt.y; return *this; }

template<typename _Tp> template<typename _Tp2> inline Point_<_Tp>::operator Point_<_Tp2>() const
{ return Point_<_Tp2>(saturate_cast<_Tp2>(x), saturate_cast<_Tp2>(y)); }
template<typename _Tp> inline Point_<_Tp>::operator Vec<_Tp, 2>() const
{ return Vec<_Tp, 2>(x, y); }

template<typename _Tp> inline _Tp Point_<_Tp>::dot(const Point_& pt) const
{ return saturate_cast<_Tp>(x*pt.x + y*pt.y); }
template<typename _Tp> inline double Point_<_Tp>::ddot(const Point_& pt) const
{ return (double)x*pt.x + (double)y*pt.y; }

template<typename _Tp> inline double Point_<_Tp>::cross(const Point_& pt) const
{ return (double)x*pt.y - (double)y*pt.x; }

template<typename _Tp> static inline Point_<_Tp>&
operator += (Point_<_Tp>& a, const Point_<_Tp>& b)
{
    a.x = saturate_cast<_Tp>(a.x + b.x);
    a.y = saturate_cast<_Tp>(a.y + b.y);
    return a;
}

template<typename _Tp> static inline Point_<_Tp>&
operator -= (Point_<_Tp>& a, const Point_<_Tp>& b)
{
    a.x = saturate_cast<_Tp>(a.x - b.x);
    a.y = saturate_cast<_Tp>(a.y - b.y);
    return a;
}

template<typename _Tp> static inline Point_<_Tp>&
operator *= (Point_<_Tp>& a, int b)
{
    a.x = saturate_cast<_Tp>(a.x*b);
    a.y = saturate_cast<_Tp>(a.y*b);
    return a;
}

template<typename _Tp> static inline Point_<_Tp>&
operator *= (Point_<_Tp>& a, float b)
{
    a.x = saturate_cast<_Tp>(a.x*b);
    a.y = saturate_cast<_Tp>(a.y*b);
    return a;
}

template<typename _Tp> static inline Point_<_Tp>&
operator *= (Point_<_Tp>& a, double b)
{
    a.x = saturate_cast<_Tp>(a.x*b);
    a.y = saturate_cast<_Tp>(a.y*b);
    return a;
}

template<typename _Tp> static inline double norm(const Point_<_Tp>& pt)
{ return std::sqrt((double)pt.x*pt.x + (double)pt.y*pt.y); }

template<typename _Tp> static inline bool operator == (const Point_<_Tp>& a, const Point_<_Tp>& b)
{ return a.x == b.x && a.y == b.y; }

template<typename _Tp> static inline bool operator != (const Point_<_Tp>& a, const Point_<_Tp>& b)
{ return a.x != b.x || a.y != b.y; }

template<typename _Tp> static inline Point_<_Tp> operator + (const Point_<_Tp>& a, const Point_<_Tp>& b)
{ return Point_<_Tp>( saturate_cast<_Tp>(a.x + b.x), saturate_cast<_Tp>(a.y + b.y) ); }

template<typename _Tp> static inline Point_<_Tp> operator - (const Point_<_Tp>& a, const Point_<_Tp>& b)
{ return Point_<_Tp>( saturate_cast<_Tp>(a.x - b.x), saturate_cast<_Tp>(a.y - b.y) ); }

template<typename _Tp> static inline Point_<_Tp> operator - (const Point_<_Tp>& a)
{ return Point_<_Tp>( saturate_cast<_Tp>(-a.x), saturate_cast<_Tp>(-a.y) ); }

template<typename _Tp> static inline Point_<_Tp> operator * (const Point_<_Tp>& a, int b)
{ return Point_<_Tp>( saturate_cast<_Tp>(a.x*b), saturate_cast<_Tp>(a.y*b) ); }

template<typename _Tp> static inline Point_<_Tp> operator * (int a, const Point_<_Tp>& b)
{ return Point_<_Tp>( saturate_cast<_Tp>(b.x*a), saturate_cast<_Tp>(b.y*a) ); }

template<typename _Tp> static inline Point_<_Tp> operator * (const Point_<_Tp>& a, float b)
{ return Point_<_Tp>( saturate_cast<_Tp>(a.x*b), saturate_cast<_Tp>(a.y*b) ); }

template<typename _Tp> static inline Point_<_Tp> operator * (float a, const Point_<_Tp>& b)
{ return Point_<_Tp>( saturate_cast<_Tp>(b.x*a), saturate_cast<_Tp>(b.y*a) ); }

template<typename _Tp> static inline Point_<_Tp> operator * (const Point_<_Tp>& a, double b)
{ return Point_<_Tp>( saturate_cast<_Tp>(a.x*b), saturate_cast<_Tp>(a.y*b) ); }

template<typename _Tp> static inline Point_<_Tp> operator * (double a, const Point_<_Tp>& b)
{ return Point_<_Tp>( saturate_cast<_Tp>(b.x*a), saturate_cast<_Tp>(b.y*a) ); }

//////////////////////////////// 3D Point ////////////////////////////////

template<typename _Tp> inline Point3_<_Tp>::Point3_() : x(0), y(0), z(0) {}
template<typename _Tp> inline Point3_<_Tp>::Point3_(_Tp _x, _Tp _y, _Tp _z) : x(_x), y(_y), z(_z) {}
template<typename _Tp> inline Point3_<_Tp>::Point3_(const Point3_& pt) : x(pt.x), y(pt.y), z(pt.z) {}
template<typename _Tp> inline Point3_<_Tp>::Point3_(const Point_<_Tp>& pt) : x(pt.x), y(pt.y), z(_Tp()) {}
template<typename _Tp> inline Point3_<_Tp>::Point3_(const Vec<_Tp, 3>& v) : x(v[0]), y(v[1]), z(v[2]) {}

template<typename _Tp> template<typename _Tp2> inline Point3_<_Tp>::operator Point3_<_Tp2>() const
{ return Point3_<_Tp2>(saturate_cast<_Tp2>(x), saturate_cast<_Tp2>(y), saturate_cast<_Tp2>(z)); }

template<typename _Tp> inline Point3_<_Tp>::operator Vec<_Tp, 3>() const
{ return Vec<_Tp, 3>(x, y, z); }

template<typename _Tp> inline Point3_<_Tp>& Point3_<_Tp>::operator = (const Point3_& pt)
{ x = pt.x; y = pt.y; z = pt.z; return *this; }

template<typename _Tp> inline _Tp Point3_<_Tp>::dot(const Point3_& pt) const
{ return saturate_cast<_Tp>(x*pt.x + y*pt.y + z*pt.z); }
template<typename _Tp> inline double Point3_<_Tp>::ddot(const Point3_& pt) const
{ return (double)x*pt.x + (double)y*pt.y + (double)z*pt.z; }

template<typename _Tp> inline Point3_<_Tp> Point3_<_Tp>::cross(const Point3_<_Tp>& pt) const
{
    return Point3_<_Tp>(y*pt.z - z*pt.y, z*pt.x - x*pt.z, x*pt.y - y*pt.x);
}

template<typename _Tp> static inline Point3_<_Tp>&
operator += (Point3_<_Tp>& a, const Point3_<_Tp>& b)
{
    a.x = saturate_cast<_Tp>(a.x + b.x);
    a.y = saturate_cast<_Tp>(a.y + b.y);
    a.z = saturate_cast<_Tp>(a.z + b.z);
    return a;
}

template<typename _Tp> static inline Point3_<_Tp>&
operator -= (Point3_<_Tp>& a, const Point3_<_Tp>& b)
{
    a.x = saturate_cast<_Tp>(a.x - b.x);
    a.y = saturate_cast<_Tp>(a.y - b.y);
    a.z = saturate_cast<_Tp>(a.z - b.z);
    return a;
}

template<typename _Tp> static inline Point3_<_Tp>&
operator *= (Point3_<_Tp>& a, int b)
{
    a.x = saturate_cast<_Tp>(a.x*b);
    a.y = saturate_cast<_Tp>(a.y*b);
    a.z = saturate_cast<_Tp>(a.z*b);
    return a;
}

template<typename _Tp> static inline Point3_<_Tp>&
operator *= (Point3_<_Tp>& a, float b)
{
    a.x = saturate_cast<_Tp>(a.x*b);
    a.y = saturate_cast<_Tp>(a.y*b);
    a.z = saturate_cast<_Tp>(a.z*b);
    return a;
}

template<typename _Tp> static inline Point3_<_Tp>&
operator *= (Point3_<_Tp>& a, double b)
{
    a.x = saturate_cast<_Tp>(a.x*b);
    a.y = saturate_cast<_Tp>(a.y*b);
    a.z = saturate_cast<_Tp>(a.z*b);
    return a;
}

template<typename _Tp> static inline double norm(const Point3_<_Tp>& pt)
{ return std::sqrt((double)pt.x*pt.x + (double)pt.y*pt.y + (double)pt.z*pt.z); }

template<typename _Tp> static inline bool operator == (const Point3_<_Tp>& a, const Point3_<_Tp>& b)
{ return a.x == b.x && a.y == b.y && a.z == b.z; }

template<typename _Tp> static inline bool operator != (const Point3_<_Tp>& a, const Point3_<_Tp>& b)
{ return a.x != b.x || a.y != b.y || a.z != b.z; }

template<typename _Tp> static inline Point3_<_Tp> operator + (const Point3_<_Tp>& a, const Point3_<_Tp>& b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(a.x + b.x),
                      saturate_cast<_Tp>(a.y + b.y),
                      saturate_cast<_Tp>(a.z + b.z)); }

template<typename _Tp> static inline Point3_<_Tp> operator - (const Point3_<_Tp>& a, const Point3_<_Tp>& b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(a.x - b.x),
                        saturate_cast<_Tp>(a.y - b.y),
                        saturate_cast<_Tp>(a.z - b.z)); }

template<typename _Tp> static inline Point3_<_Tp> operator - (const Point3_<_Tp>& a)
{ return Point3_<_Tp>( saturate_cast<_Tp>(-a.x),
                      saturate_cast<_Tp>(-a.y),
                      saturate_cast<_Tp>(-a.z) ); }

template<typename _Tp> static inline Point3_<_Tp> operator * (const Point3_<_Tp>& a, int b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(a.x*b),
                      saturate_cast<_Tp>(a.y*b),
                      saturate_cast<_Tp>(a.z*b) ); }

template<typename _Tp> static inline Point3_<_Tp> operator * (int a, const Point3_<_Tp>& b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(b.x*a),
                      saturate_cast<_Tp>(b.y*a),
                      saturate_cast<_Tp>(b.z*a) ); }

template<typename _Tp> static inline Point3_<_Tp> operator * (const Point3_<_Tp>& a, float b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(a.x*b),
                      saturate_cast<_Tp>(a.y*b),
                      saturate_cast<_Tp>(a.z*b) ); }

template<typename _Tp> static inline Point3_<_Tp> operator * (float a, const Point3_<_Tp>& b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(b.x*a),
                      saturate_cast<_Tp>(b.y*a),
                      saturate_cast<_Tp>(b.z*a) ); }

template<typename _Tp> static inline Point3_<_Tp> operator * (const Point3_<_Tp>& a, double b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(a.x*b),
                      saturate_cast<_Tp>(a.y*b),
                      saturate_cast<_Tp>(a.z*b) ); }

template<typename _Tp> static inline Point3_<_Tp> operator * (double a, const Point3_<_Tp>& b)
{ return Point3_<_Tp>( saturate_cast<_Tp>(b.x*a),
                      saturate_cast<_Tp>(b.y*a),
                      saturate_cast<_Tp>(b.z*a) ); }

//////////////////////////////// Size ////////////////////////////////

template<typename _Tp> inline Size_<_Tp>::Size_()
    : width(0), height(0) {}
template<typename _Tp> inline Size_<_Tp>::Size_(_Tp _width, _Tp _height)
    : width(_width), height(_height) {}
template<typename _Tp> inline Size_<_Tp>::Size_(const Size_& sz)
    : width(sz.width), height(sz.height) {}
template<typename _Tp> inline Size_<_Tp>::Size_(const CvSize& sz)
    : width(saturate_cast<_Tp>(sz.width)), height(saturate_cast<_Tp>(sz.height)) {}
template<typename _Tp> inline Size_<_Tp>::Size_(const CvSize2D32f& sz)
    : width(saturate_cast<_Tp>(sz.width)), height(saturate_cast<_Tp>(sz.height)) {}
template<typename _Tp> inline Size_<_Tp>::Size_(const Point_<_Tp>& pt) : width(pt.x), height(pt.y) {}

template<typename _Tp> template<typename _Tp2> inline Size_<_Tp>::operator Size_<_Tp2>() const
{ return Size_<_Tp2>(saturate_cast<_Tp2>(width), saturate_cast<_Tp2>(height)); }
template<typename _Tp> inline Size_<_Tp>::operator CvSize() const
{ return cvSize(saturate_cast<int>(width), saturate_cast<int>(height)); }
template<typename _Tp> inline Size_<_Tp>::operator CvSize2D32f() const
{ return cvSize2D32f((float)width, (float)height); }

template<typename _Tp> inline Size_<_Tp>& Size_<_Tp>::operator = (const Size_<_Tp>& sz)
{ width = sz.width; height = sz.height; return *this; }
template<typename _Tp> static inline Size_<_Tp> operator * (const Size_<_Tp>& a, _Tp b)
{ return Size_<_Tp>(a.width * b, a.height * b); }
template<typename _Tp> static inline Size_<_Tp> operator + (const Size_<_Tp>& a, const Size_<_Tp>& b)
{ return Size_<_Tp>(a.width + b.width, a.height + b.height); }
template<typename _Tp> static inline Size_<_Tp> operator - (const Size_<_Tp>& a, const Size_<_Tp>& b)
{ return Size_<_Tp>(a.width - b.width, a.height - b.height); }
template<typename _Tp> inline _Tp Size_<_Tp>::area() const { return width*height; }

template<typename _Tp> static inline Size_<_Tp>& operator += (Size_<_Tp>& a, const Size_<_Tp>& b)
{ a.width += b.width; a.height += b.height; return a; }
template<typename _Tp> static inline Size_<_Tp>& operator -= (Size_<_Tp>& a, const Size_<_Tp>& b)
{ a.width -= b.width; a.height -= b.height; return a; }

template<typename _Tp> static inline bool operator == (const Size_<_Tp>& a, const Size_<_Tp>& b)
{ return a.width == b.width && a.height == b.height; }
template<typename _Tp> static inline bool operator != (const Size_<_Tp>& a, const Size_<_Tp>& b)
{ return a.width != b.width || a.height != b.height; }

//////////////////////////////// Rect ////////////////////////////////


template<typename _Tp> inline Rect_<_Tp>::Rect_() : x(0), y(0), width(0), height(0) {}
template<typename _Tp> inline Rect_<_Tp>::Rect_(_Tp _x, _Tp _y, _Tp _width, _Tp _height) : x(_x), y(_y), width(_width), height(_height) {}
template<typename _Tp> inline Rect_<_Tp>::Rect_(const Rect_<_Tp>& r) : x(r.x), y(r.y), width(r.width), height(r.height) {}
template<typename _Tp> inline Rect_<_Tp>::Rect_(const CvRect& r) : x((_Tp)r.x), y((_Tp)r.y), width((_Tp)r.width), height((_Tp)r.height) {}
template<typename _Tp> inline Rect_<_Tp>::Rect_(const Point_<_Tp>& org, const Size_<_Tp>& sz) :
    x(org.x), y(org.y), width(sz.width), height(sz.height) {}
template<typename _Tp> inline Rect_<_Tp>::Rect_(const Point_<_Tp>& pt1, const Point_<_Tp>& pt2)
{
    x = std::min(pt1.x, pt2.x); y = std::min(pt1.y, pt2.y);
    width = std::max(pt1.x, pt2.x) - x; height = std::max(pt1.y, pt2.y) - y;
}
template<typename _Tp> inline Rect_<_Tp>& Rect_<_Tp>::operator = ( const Rect_<_Tp>& r )
{ x = r.x; y = r.y; width = r.width; height = r.height; return *this; }

template<typename _Tp> inline Point_<_Tp> Rect_<_Tp>::tl() const { return Point_<_Tp>(x,y); }
template<typename _Tp> inline Point_<_Tp> Rect_<_Tp>::br() const { return Point_<_Tp>(x+width, y+height); }

template<typename _Tp> static inline Rect_<_Tp>& operator += ( Rect_<_Tp>& a, const Point_<_Tp>& b )
{ a.x += b.x; a.y += b.y; return a; }
template<typename _Tp> static inline Rect_<_Tp>& operator -= ( Rect_<_Tp>& a, const Point_<_Tp>& b )
{ a.x -= b.x; a.y -= b.y; return a; }

template<typename _Tp> static inline Rect_<_Tp>& operator += ( Rect_<_Tp>& a, const Size_<_Tp>& b )
{ a.width += b.width; a.height += b.height; return a; }

template<typename _Tp> static inline Rect_<_Tp>& operator -= ( Rect_<_Tp>& a, const Size_<_Tp>& b )
{ a.width -= b.width; a.height -= b.height; return a; }

template<typename _Tp> static inline Rect_<_Tp>& operator &= ( Rect_<_Tp>& a, const Rect_<_Tp>& b )
{
    _Tp x1 = std::max(a.x, b.x), y1 = std::max(a.y, b.y);
    a.width = std::min(a.x + a.width, b.x + b.width) - x1;
    a.height = std::min(a.y + a.height, b.y + b.height) - y1;
    a.x = x1; a.y = y1;
    if( a.width <= 0 || a.height <= 0 )
        a = Rect();
    return a;
}

template<typename _Tp> static inline Rect_<_Tp>& operator |= ( Rect_<_Tp>& a, const Rect_<_Tp>& b )
{
    _Tp x1 = std::min(a.x, b.x), y1 = std::min(a.y, b.y);
    a.width = std::max(a.x + a.width, b.x + b.width) - x1;
    a.height = std::max(a.y + a.height, b.y + b.height) - y1;
    a.x = x1; a.y = y1;
    return a;
}

template<typename _Tp> inline Size_<_Tp> Rect_<_Tp>::size() const { return Size_<_Tp>(width, height); }
template<typename _Tp> inline _Tp Rect_<_Tp>::area() const { return width*height; }

template<typename _Tp> template<typename _Tp2> inline Rect_<_Tp>::operator Rect_<_Tp2>() const
{ return Rect_<_Tp2>(saturate_cast<_Tp2>(x), saturate_cast<_Tp2>(y),
                     saturate_cast<_Tp2>(width), saturate_cast<_Tp2>(height)); }
template<typename _Tp> inline Rect_<_Tp>::operator CvRect() const
{ return cvRect(saturate_cast<int>(x), saturate_cast<int>(y),
                saturate_cast<int>(width), saturate_cast<int>(height)); }

template<typename _Tp> inline bool Rect_<_Tp>::contains(const Point_<_Tp>& pt) const
{ return x <= pt.x && pt.x < x + width && y <= pt.y && pt.y < y + height; }

template<typename _Tp> static inline bool operator == (const Rect_<_Tp>& a, const Rect_<_Tp>& b)
{
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}

template<typename _Tp> static inline bool operator != (const Rect_<_Tp>& a, const Rect_<_Tp>& b)
{
    return a.x != b.x || a.y != b.y || a.width != b.width || a.height != b.height;
}

template<typename _Tp> static inline Rect_<_Tp> operator + (const Rect_<_Tp>& a, const Point_<_Tp>& b)
{
    return Rect_<_Tp>( a.x + b.x, a.y + b.y, a.width, a.height );
}

template<typename _Tp> static inline Rect_<_Tp> operator - (const Rect_<_Tp>& a, const Point_<_Tp>& b)
{
    return Rect_<_Tp>( a.x - b.x, a.y - b.y, a.width, a.height );
}

template<typename _Tp> static inline Rect_<_Tp> operator + (const Rect_<_Tp>& a, const Size_<_Tp>& b)
{
    return Rect_<_Tp>( a.x, a.y, a.width + b.width, a.height + b.height );
}

template<typename _Tp> static inline Rect_<_Tp> operator & (const Rect_<_Tp>& a, const Rect_<_Tp>& b)
{
    Rect_<_Tp> c = a;
    return c &= b;
}

template<typename _Tp> static inline Rect_<_Tp> operator | (const Rect_<_Tp>& a, const Rect_<_Tp>& b)
{
    Rect_<_Tp> c = a;
    return c |= b;
}

template<typename _Tp> inline bool Point_<_Tp>::inside( const Rect_<_Tp>& r ) const
{
    return r.contains(*this);
}

inline RotatedRect::RotatedRect() { angle = 0; }
inline RotatedRect::RotatedRect(const Point2f& _center, const Size2f& _size, float _angle)
    : center(_center), size(_size), angle(_angle) {}
inline RotatedRect::RotatedRect(const CvBox2D& box)
    : center(box.center), size(box.size), angle(box.angle) {}
inline RotatedRect::operator CvBox2D() const
{
    CvBox2D box; box.center = center; box.size = size; box.angle = angle;
    return box;
}

//////////////////////////////// Scalar_ ///////////////////////////////

template<typename _Tp> inline Scalar_<_Tp>::Scalar_()
{ this->val[0] = this->val[1] = this->val[2] = this->val[3] = 0; }

template<typename _Tp> inline Scalar_<_Tp>::Scalar_(_Tp v0, _Tp v1, _Tp v2, _Tp v3)
{ this->val[0] = v0; this->val[1] = v1; this->val[2] = v2; this->val[3] = v3; }

template<typename _Tp> inline Scalar_<_Tp>::Scalar_(const CvScalar& s)
{
    this->val[0] = saturate_cast<_Tp>(s.val[0]);
    this->val[1] = saturate_cast<_Tp>(s.val[1]);
    this->val[2] = saturate_cast<_Tp>(s.val[2]);
    this->val[3] = saturate_cast<_Tp>(s.val[3]);
}

template<typename _Tp> inline Scalar_<_Tp>::Scalar_(_Tp v0)
{ this->val[0] = v0; this->val[1] = this->val[2] = this->val[3] = 0; }

template<typename _Tp> inline Scalar_<_Tp> Scalar_<_Tp>::all(_Tp v0)
{ return Scalar_<_Tp>(v0, v0, v0, v0); }
template<typename _Tp> inline Scalar_<_Tp>::operator CvScalar() const
{ return cvScalar(this->val[0], this->val[1], this->val[2], this->val[3]); }

template<typename _Tp> template<typename T2> inline Scalar_<_Tp>::operator Scalar_<T2>() const
{
    return Scalar_<T2>(saturate_cast<T2>(this->val[0]),
                  saturate_cast<T2>(this->val[1]),
                  saturate_cast<T2>(this->val[2]),
                  saturate_cast<T2>(this->val[3]));
}

template<typename _Tp> static inline Scalar_<_Tp>& operator += (Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    a.val[0] = saturate_cast<_Tp>(a.val[0] + b.val[0]);
    a.val[1] = saturate_cast<_Tp>(a.val[1] + b.val[1]);
    a.val[2] = saturate_cast<_Tp>(a.val[2] + b.val[2]);
    a.val[3] = saturate_cast<_Tp>(a.val[3] + b.val[3]);
    return a;
}

template<typename _Tp> static inline Scalar_<_Tp>& operator -= (Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    a.val[0] = saturate_cast<_Tp>(a.val[0] - b.val[0]);
    a.val[1] = saturate_cast<_Tp>(a.val[1] - b.val[1]);
    a.val[2] = saturate_cast<_Tp>(a.val[2] - b.val[2]);
    a.val[3] = saturate_cast<_Tp>(a.val[3] - b.val[3]);
    return a;
}

template<typename _Tp> static inline Scalar_<_Tp>& operator *= ( Scalar_<_Tp>& a, _Tp v )
{
    a.val[0] = saturate_cast<_Tp>(a.val[0] * v);
    a.val[1] = saturate_cast<_Tp>(a.val[1] * v);
    a.val[2] = saturate_cast<_Tp>(a.val[2] * v);
    a.val[3] = saturate_cast<_Tp>(a.val[3] * v);
    return a;
}

template<typename _Tp> inline Scalar_<_Tp> Scalar_<_Tp>::mul(const Scalar_<_Tp>& t, double scale ) const
{
    return Scalar_<_Tp>( saturate_cast<_Tp>(this->val[0]*t.val[0]*scale),
                       saturate_cast<_Tp>(this->val[1]*t.val[1]*scale),
                       saturate_cast<_Tp>(this->val[2]*t.val[2]*scale),
                       saturate_cast<_Tp>(this->val[3]*t.val[3]*scale));
}

template<typename _Tp> static inline bool operator == ( const Scalar_<_Tp>& a, const Scalar_<_Tp>& b )
{
    return a.val[0] == b.val[0] && a.val[1] == b.val[1] &&
        a.val[2] == b.val[2] && a.val[3] == b.val[3];
}

template<typename _Tp> static inline bool operator != ( const Scalar_<_Tp>& a, const Scalar_<_Tp>& b )
{
    return a.val[0] != b.val[0] || a.val[1] != b.val[1] ||
        a.val[2] != b.val[2] || a.val[3] != b.val[3];
}

template<typename _Tp> static inline Scalar_<_Tp> operator + (const Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(a.val[0] + b.val[0]),
                      saturate_cast<_Tp>(a.val[1] + b.val[1]),
                      saturate_cast<_Tp>(a.val[2] + b.val[2]),
                      saturate_cast<_Tp>(a.val[3] + b.val[3]));
}

template<typename _Tp> static inline Scalar_<_Tp> operator - (const Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(a.val[0] - b.val[0]),
                      saturate_cast<_Tp>(a.val[1] - b.val[1]),
                      saturate_cast<_Tp>(a.val[2] - b.val[2]),
                      saturate_cast<_Tp>(a.val[3] - b.val[3]));
}

template<typename _Tp> static inline Scalar_<_Tp> operator * (const Scalar_<_Tp>& a, _Tp alpha)
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(a.val[0] * alpha),
                      saturate_cast<_Tp>(a.val[1] * alpha),
                      saturate_cast<_Tp>(a.val[2] * alpha),
                      saturate_cast<_Tp>(a.val[3] * alpha));
}

template<typename _Tp> static inline Scalar_<_Tp> operator * (_Tp alpha, const Scalar_<_Tp>& a)
{
    return a*alpha;
}

template<typename _Tp> static inline Scalar_<_Tp> operator - (const Scalar_<_Tp>& a)
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(-a.val[0]), saturate_cast<_Tp>(-a.val[1]),
                      saturate_cast<_Tp>(-a.val[2]), saturate_cast<_Tp>(-a.val[3]));
}


template<typename _Tp> static inline Scalar_<_Tp>
operator * (const Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3]),
                        saturate_cast<_Tp>(a[0]*b[1] + a[1]*b[0] + a[2]*b[3] - a[3]*b[2]),
                        saturate_cast<_Tp>(a[0]*b[2] - a[1]*b[3] + a[2]*b[0] + a[3]*b[1]),
                        saturate_cast<_Tp>(a[0]*b[3] + a[1]*b[2] - a[2]*b[1] + a[3]*b[0]));
}

template<typename _Tp> static inline Scalar_<_Tp>&
operator *= (Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    a = a*b;
    return a;
}

template<typename _Tp> inline Scalar_<_Tp> Scalar_<_Tp>::conj() const
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(this->val[0]),
                        saturate_cast<_Tp>(-this->val[1]),
                        saturate_cast<_Tp>(-this->val[2]),
                        saturate_cast<_Tp>(-this->val[3]));
}

template<typename _Tp> inline bool Scalar_<_Tp>::isReal() const
{
    return this->val[1] == 0 && this->val[2] == 0 && this->val[3] == 0;
}

template<typename _Tp> static inline
Scalar_<_Tp> operator / (const Scalar_<_Tp>& a, _Tp alpha)
{
    return Scalar_<_Tp>(saturate_cast<_Tp>(a.val[0] / alpha),
                        saturate_cast<_Tp>(a.val[1] / alpha),
                        saturate_cast<_Tp>(a.val[2] / alpha),
                        saturate_cast<_Tp>(a.val[3] / alpha));
}

template<typename _Tp> static inline
Scalar_<float> operator / (const Scalar_<float>& a, float alpha)
{
    float s = 1/alpha;
    return Scalar_<float>(a.val[0]*s, a.val[1]*s, a.val[2]*s, a.val[3]*s);
}

template<typename _Tp> static inline
Scalar_<double> operator / (const Scalar_<double>& a, double alpha)
{
    double s = 1/alpha;
    return Scalar_<double>(a.val[0]*s, a.val[1]*s, a.val[2]*s, a.val[3]*s);
}

template<typename _Tp> static inline
Scalar_<_Tp>& operator /= (Scalar_<_Tp>& a, _Tp alpha)
{
    a = a/alpha;
    return a;
}

template<typename _Tp> static inline
Scalar_<_Tp> operator / (_Tp a, const Scalar_<_Tp>& b)
{
    _Tp s = a/(b[0]*b[0] + b[1]*b[1] + b[2]*b[2] + b[3]*b[3]);
    return b.conj()*s;
}

template<typename _Tp> static inline
Scalar_<_Tp> operator / (const Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    return a*((_Tp)1/b);
}

template<typename _Tp> static inline
Scalar_<_Tp>& operator /= (Scalar_<_Tp>& a, const Scalar_<_Tp>& b)
{
    a = a/b;
    return a;
}

//////////////////////////////// Range /////////////////////////////////

inline Range::Range() : start(0), end(0) {}
inline Range::Range(int _start, int _end) : start(_start), end(_end) {}
inline Range::Range(const CvSlice& slice) : start(slice.start_index), end(slice.end_index)
{
    if( start == 0 && end == CV_WHOLE_SEQ_END_INDEX )
        *this = Range::all();
}

inline int Range::size() const { return end - start; }
inline bool Range::empty() const { return start == end; }
inline Range Range::all() { return Range(INT_MIN, INT_MAX); }

static inline bool operator == (const Range& r1, const Range& r2)
{ return r1.start == r2.start && r1.end == r2.end; }

static inline bool operator != (const Range& r1, const Range& r2)
{ return !(r1 == r2); }

static inline bool operator !(const Range& r)
{ return r.start == r.end; }

static inline Range operator & (const Range& r1, const Range& r2)
{
    Range r(std::max(r1.start, r2.start), std::min(r1.end, r2.end));
    r.end = std::max(r.end, r.start);
    return r;
}

static inline Range& operator &= (Range& r1, const Range& r2)
{
    r1 = r1 & r2;
    return r1;
}

static inline Range operator + (const Range& r1, int delta)
{
    return Range(r1.start + delta, r1.end + delta);
}

static inline Range operator + (int delta, const Range& r1)
{
    return Range(r1.start + delta, r1.end + delta);
}

static inline Range operator - (const Range& r1, int delta)
{
    return r1 + (-delta);
}

inline Range::operator CvSlice() const
{ return *this != Range::all() ? cvSlice(start, end) : CV_WHOLE_SEQ; }



//////////////////////////////// Vector ////////////////////////////////

// template vector class. It is similar to STL's vector,
// with a few important differences:
//   1) it can be created on top of user-allocated data w/o copying it
//   2) vector b = a means copying the header,
//      not the underlying data (use clone() to make a deep copy)
template <typename _Tp> class CV_EXPORTS Vector
{
public:
    typedef _Tp value_type;
    typedef _Tp* iterator;
    typedef const _Tp* const_iterator;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;

    struct CV_EXPORTS Hdr
    {
        Hdr() : data(0), datastart(0), refcount(0), size(0), capacity(0) {};
        _Tp* data;
        _Tp* datastart;
        int* refcount;
        size_t size;
        size_t capacity;
    };

    Vector() {}
    Vector(size_t _size)  { resize(_size); }
    Vector(size_t _size, const _Tp& val)
    {
        resize(_size);
        for(size_t i = 0; i < _size; i++)
            hdr.data[i] = val;
    }
    Vector(_Tp* _data, size_t _size, bool _copyData=false)
    { set(_data, _size, _copyData); }

    template<int n> Vector(const Vec<_Tp, n>& vec)
    { set((_Tp*)&vec.val[0], n, true); }

    Vector(const std::vector<_Tp>& vec, bool _copyData=false)
    { set(!vec.empty() ? (_Tp*)&vec[0] : 0, vec.size(), _copyData); }

    Vector(const Vector& d) { *this = d; }

    Vector(const Vector& d, const Range& r_)
    {
        Range r = r_ == Range::all() ? Range(0, d.size()) : r_;
        /*if( r == Range::all() )
            r = Range(0, d.size());*/
        if( r.size() > 0 && r.start >= 0 && r.end <= d.size() )
        {
            if( d.hdr.refcount )
                CV_XADD(d.hdr.refcount, 1);
            hdr.refcount = d.hdr.refcount;
            hdr.datastart = d.hdr.datastart;
            hdr.data = d.hdr.data + r.start;
            hdr.capacity = hdr.size = r.size();
        }
    }

    Vector<_Tp>& operator = (const Vector& d)
    {
        if( this != &d )
        {
            if( d.hdr.refcount )
                CV_XADD(d.hdr.refcount, 1);
            release();
            hdr = d.hdr;
        }
        return *this;
    }

    ~Vector()  { release(); }

    Vector<_Tp> clone() const
    { return hdr.data ? Vector<_Tp>(hdr.data, hdr.size, true) : Vector<_Tp>(); }

    void copyTo(Vector<_Tp>& vec) const
    {
        size_t i, sz = size();
        vec.resize(sz);
        const _Tp* src = hdr.data;
        _Tp* dst = vec.hdr.data;
        for( i = 0; i < sz; i++ )
            dst[i] = src[i];
    }

    void copyTo(std::vector<_Tp>& vec) const
    {
        size_t i, sz = size();
        vec.resize(sz);
        const _Tp* src = hdr.data;
        _Tp* dst = sz ? &vec[0] : 0;
        for( i = 0; i < sz; i++ )
            dst[i] = src[i];
    }

    operator CvMat() const
    { return cvMat((int)size(), 1, type(), (void*)hdr.data); }

    _Tp& operator [] (size_t i) { CV_DbgAssert( i < size() ); return hdr.data[i]; }
    const _Tp& operator [] (size_t i) const { CV_DbgAssert( i < size() ); return hdr.data[i]; }
    Vector operator() (const Range& r) const { return Vector(*this, r); }
    _Tp& back() { CV_DbgAssert(!empty()); return hdr.data[hdr.size-1]; }
    const _Tp& back() const { CV_DbgAssert(!empty()); return hdr.data[hdr.size-1]; }
    _Tp& front() { CV_DbgAssert(!empty()); return hdr.data[0]; }
    const _Tp& front() const { CV_DbgAssert(!empty()); return hdr.data[0]; }

    _Tp* begin() { return hdr.data; }
    _Tp* end() { return hdr.data + hdr.size; }
    const _Tp* begin() const { return hdr.data; }
    const _Tp* end() const { return hdr.data + hdr.size; }

    void addref() { if( hdr.refcount ) CV_XADD(hdr.refcount, 1); }
    void release()
    {
        if( hdr.refcount && CV_XADD(hdr.refcount, -1) == 1 )
        {
            delete[] hdr.datastart;
            delete hdr.refcount;
        }
        hdr = Hdr();
    }

    void set(_Tp* _data, size_t _size, bool _copyData=false)
    {
        if( !_copyData )
        {
            release();
            hdr.data = hdr.datastart = _data;
            hdr.size = hdr.capacity = _size;
            hdr.refcount = 0;
        }
        else
        {
            reserve(_size);
            for( size_t i = 0; i < _size; i++ )
                hdr.data[i] = _data[i];
            hdr.size = _size;
        }
    }

    void reserve(size_t newCapacity)
    {
        _Tp* newData;
        int* newRefcount;
        size_t i, oldSize = hdr.size;
        if( (!hdr.refcount || *hdr.refcount == 1) && hdr.capacity >= newCapacity )
            return;
        newCapacity = std::max(newCapacity, oldSize);
        newData = new _Tp[newCapacity];
        newRefcount = new int(1);
        for( i = 0; i < oldSize; i++ )
            newData[i] = hdr.data[i];
        release();
        hdr.data = hdr.datastart = newData;
        hdr.capacity = newCapacity;
        hdr.size = oldSize;
        hdr.refcount = newRefcount;
    }

    void resize(size_t newSize)
    {
        size_t i;
        newSize = std::max(newSize, (size_t)0);
        if( (!hdr.refcount || *hdr.refcount == 1) && hdr.size == newSize )
            return;
        if( newSize > hdr.capacity )
            reserve(std::max(newSize, std::max((size_t)4, hdr.capacity*2)));
        for( i = hdr.size; i < newSize; i++ )
            hdr.data[i] = _Tp();
        hdr.size = newSize;
    }

    Vector<_Tp>& push_back(const _Tp& elem)
    {
        if( hdr.size == hdr.capacity )
            reserve( std::max((size_t)4, hdr.capacity*2) );
        hdr.data[hdr.size++] = elem;
        return *this;
    }

    Vector<_Tp>& pop_back()
    {
        if( hdr.size > 0 )
            --hdr.size;
        return *this;
    }

    size_t size() const { return hdr.size; }
    size_t capacity() const { return hdr.capacity; }
    bool empty() const { return hdr.size == 0; }
    void clear() { resize(0); }
    int type() const { return DataType<_Tp>::type; }

protected:
    Hdr hdr;
};


template<typename _Tp> inline typename DataType<_Tp>::work_type
dot(const Vector<_Tp>& v1, const Vector<_Tp>& v2)
{
    typedef typename DataType<_Tp>::work_type _Tw;
    size_t i = 0, n = v1.size();
    assert(v1.size() == v2.size());

    _Tw s = 0;
    const _Tp *ptr1 = &v1[0], *ptr2 = &v2[0];
    for( ; i < n; i++ )
        s += (_Tw)ptr1[i]*ptr2[i];

    return s;
}

// Multiply-with-Carry RNG
inline RNG::RNG() { state = 0xffffffff; }
inline RNG::RNG(uint64 _state) { state = _state ? _state : 0xffffffff; }
inline unsigned RNG::next()
{
    state = (uint64)(unsigned)state*CV_RNG_COEFF + (unsigned)(state >> 32);
    return (unsigned)state;
}

inline RNG::operator uchar() { return (uchar)next(); }
inline RNG::operator schar() { return (schar)next(); }
inline RNG::operator ushort() { return (ushort)next(); }
inline RNG::operator short() { return (short)next(); }
inline RNG::operator unsigned() { return next(); }
inline unsigned RNG::operator ()(unsigned N) {return (unsigned)uniform(0,N);}
inline unsigned RNG::operator ()() {return next();}
inline RNG::operator int() { return (int)next(); }
// * (2^32-1)^-1
inline RNG::operator float() { return next()*2.3283064365386962890625e-10f; }
inline RNG::operator double()
{
    unsigned t = next();
    return (((uint64)t << 32) | next())*5.4210108624275221700372640043497e-20;
}
inline int RNG::uniform(int a, int b) { return a == b ? a : (int)(next()%(b - a) + a); }
inline float RNG::uniform(float a, float b) { return ((float)*this)*(b - a) + a; }
inline double RNG::uniform(double a, double b) { return ((double)*this)*(b - a) + a; }

inline TermCriteria::TermCriteria() : type(0), maxCount(0), epsilon(0) {}
inline TermCriteria::TermCriteria(int _type, int _maxCount, double _epsilon)
    : type(_type), maxCount(_maxCount), epsilon(_epsilon) {}
inline TermCriteria::TermCriteria(const CvTermCriteria& criteria)
    : type(criteria.type), maxCount(criteria.max_iter), epsilon(criteria.epsilon) {}
inline TermCriteria::operator CvTermCriteria() const
{ return cvTermCriteria(type, maxCount, epsilon); }

inline uchar* LineIterator::operator *() { return ptr; }
inline LineIterator& LineIterator::operator ++()
{
    int mask = err < 0 ? -1 : 0;
    err += minusDelta + (plusDelta & mask);
    ptr += minusStep + (plusStep & mask);
    return *this;
}
inline LineIterator LineIterator::operator ++(int)
{
    LineIterator it = *this;
    ++(*this);
    return it;
}
inline Point LineIterator::pos() const
{
    Point p;
    p.y = (int)((ptr - ptr0)/step);
    p.x = (int)(((ptr - ptr0) - p.y*step)/elemSize);
    return p;
}

/////////////////////////////////// Ptr ////////////////////////////////////////

template<typename _Tp> inline Ptr<_Tp>::Ptr() : obj(0), refcount(0) {}
template<typename _Tp> inline Ptr<_Tp>::Ptr(_Tp* _obj) : obj(_obj)
{
    if(obj)
    {
        refcount = (int*)fastMalloc(sizeof(*refcount));
        *refcount = 1;
    }
    else
        refcount = 0;
}

template<typename _Tp> inline void Ptr<_Tp>::addref()
{ if( refcount ) CV_XADD(refcount, 1); }

template<typename _Tp> inline void Ptr<_Tp>::release()
{
    if( refcount && CV_XADD(refcount, -1) == 1 )
    {
        delete_obj();
        fastFree(refcount);
    }
    refcount = 0;
    obj = 0;
}

template<typename _Tp> inline void Ptr<_Tp>::delete_obj()
{
    if( obj ) delete obj;
}

template<typename _Tp> inline Ptr<_Tp>::~Ptr() { release(); }

template<typename _Tp> inline Ptr<_Tp>::Ptr(const Ptr<_Tp>& _ptr)
{
    obj = _ptr.obj;
    refcount = _ptr.refcount;
    addref();
}

template<typename _Tp> inline Ptr<_Tp>& Ptr<_Tp>::operator = (const Ptr<_Tp>& _ptr)
{
    int* _refcount = _ptr.refcount;
    if( _refcount )
        CV_XADD(_refcount, 1);
    release();
    obj = _ptr.obj;
    refcount = _refcount;
    return *this;
}

template<typename _Tp> inline _Tp* Ptr<_Tp>::operator -> () { return obj; }
template<typename _Tp> inline const _Tp* Ptr<_Tp>::operator -> () const { return obj; }

template<typename _Tp> inline Ptr<_Tp>::operator _Tp* () { return obj; }
template<typename _Tp> inline Ptr<_Tp>::operator const _Tp*() const { return obj; }

template<typename _Tp> inline bool Ptr<_Tp>::empty() const { return obj == 0; }

template<typename _Tp> template<typename _Tp2> Ptr<_Tp>::Ptr(const Ptr<_Tp2>& p)
    : obj(0), refcount(0)
{
    if (p.empty())
        return;

    _Tp* p_casted = dynamic_cast<_Tp*>(p.obj);
    if (!p_casted)
        return;

    obj = p_casted;
    refcount = p.refcount;
    addref();
}

template<typename _Tp> template<typename _Tp2> inline Ptr<_Tp2> Ptr<_Tp>::ptr()
{
    Ptr<_Tp2> p;
    if( !obj )
        return p;

    _Tp2* obj_casted = dynamic_cast<_Tp2*>(obj);
    if (!obj_casted)
        return p;

    if( refcount )
        CV_XADD(refcount, 1);

    p.obj = obj_casted;
    p.refcount = refcount;
    return p;
}

template<typename _Tp> template<typename _Tp2> inline const Ptr<_Tp2> Ptr<_Tp>::ptr() const
{
    Ptr<_Tp2> p;
    if( !obj )
        return p;

    _Tp2* obj_casted = dynamic_cast<_Tp2*>(obj);
    if (!obj_casted)
        return p;

    if( refcount )
        CV_XADD(refcount, 1);

    p.obj = obj_casted;
    p.refcount = refcount;
    return p;
}

template<class _Tp, class _Tp2> inline bool operator==(const Ptr<_Tp>& a, const Ptr<_Tp2>& b) { return a.refcount == b.refcount; }
template<class _Tp, class _Tp2> inline bool operator!=(const Ptr<_Tp>& a, const Ptr<_Tp2>& b) { return a.refcount != b.refcount; }


//////////////////////////////////////// XML & YAML I/O ////////////////////////////////////

CV_EXPORTS_W void write( FileStorage& fs, const String& name, int value );
CV_EXPORTS_W void write( FileStorage& fs, const String& name, float value );
CV_EXPORTS_W void write( FileStorage& fs, const String& name, double value );
CV_EXPORTS_W void write( FileStorage& fs, const String& name, const String& value );

template<typename _Tp> inline void write(FileStorage& fs, const _Tp& value)
{ write(fs, String(), value); }

CV_EXPORTS void writeScalar( FileStorage& fs, int value );
CV_EXPORTS void writeScalar( FileStorage& fs, float value );
CV_EXPORTS void writeScalar( FileStorage& fs, double value );
CV_EXPORTS void writeScalar( FileStorage& fs, const String& value );

template<> inline void write( FileStorage& fs, const int& value )
{
    writeScalar(fs, value);
}

template<> inline void write( FileStorage& fs, const float& value )
{
    writeScalar(fs, value);
}

template<> inline void write( FileStorage& fs, const double& value )
{
    writeScalar(fs, value);
}

template<> inline void write( FileStorage& fs, const String& value )
{
    writeScalar(fs, value);
}

template<typename _Tp> inline void write(FileStorage& fs, const Point_<_Tp>& pt )
{
    write(fs, pt.x);
    write(fs, pt.y);
}

template<typename _Tp> inline void write(FileStorage& fs, const Point3_<_Tp>& pt )
{
    write(fs, pt.x);
    write(fs, pt.y);
    write(fs, pt.z);
}

template<typename _Tp> inline void write(FileStorage& fs, const Size_<_Tp>& sz )
{
    write(fs, sz.width);
    write(fs, sz.height);
}

template<typename _Tp> inline void write(FileStorage& fs, const Complex<_Tp>& c )
{
    write(fs, c.re);
    write(fs, c.im);
}

template<typename _Tp> inline void write(FileStorage& fs, const Rect_<_Tp>& r )
{
    write(fs, r.x);
    write(fs, r.y);
    write(fs, r.width);
    write(fs, r.height);
}

template<typename _Tp, int cn> inline void write(FileStorage& fs, const Vec<_Tp, cn>& v )
{
    for(int i = 0; i < cn; i++)
        write(fs, v.val[i]);
}

template<typename _Tp> inline void write(FileStorage& fs, const Scalar_<_Tp>& s )
{
    write(fs, s.val[0]);
    write(fs, s.val[1]);
    write(fs, s.val[2]);
    write(fs, s.val[3]);
}

inline void write(FileStorage& fs, const Range& r )
{
    write(fs, r.start);
    write(fs, r.end);
}

class CV_EXPORTS WriteStructContext
{
public:
    WriteStructContext(FileStorage& _fs, const String& name,
        int flags, const String& typeName=String());
    ~WriteStructContext();
    FileStorage* fs;
};

template<typename _Tp> inline void write(FileStorage& fs, const String& name, const Point_<_Tp>& pt )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, pt.x);
    write(fs, pt.y);
}

template<typename _Tp> inline void write(FileStorage& fs, const String& name, const Point3_<_Tp>& pt )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, pt.x);
    write(fs, pt.y);
    write(fs, pt.z);
}

template<typename _Tp> inline void write(FileStorage& fs, const String& name, const Size_<_Tp>& sz )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, sz.width);
    write(fs, sz.height);
}

template<typename _Tp> inline void write(FileStorage& fs, const String& name, const Complex<_Tp>& c )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, c.re);
    write(fs, c.im);
}

template<typename _Tp> inline void write(FileStorage& fs, const String& name, const Rect_<_Tp>& r )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, r.x);
    write(fs, r.y);
    write(fs, r.width);
    write(fs, r.height);
}

template<typename _Tp, int cn> inline void write(FileStorage& fs, const String& name, const Vec<_Tp, cn>& v )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    for(int i = 0; i < cn; i++)
        write(fs, v.val[i]);
}

template<typename _Tp> inline void write(FileStorage& fs, const String& name, const Scalar_<_Tp>& s )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, s.val[0]);
    write(fs, s.val[1]);
    write(fs, s.val[2]);
    write(fs, s.val[3]);
}

inline void write(FileStorage& fs, const String& name, const Range& r )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+CV_NODE_FLOW);
    write(fs, r.start);
    write(fs, r.end);
}

template<typename _Tp, int numflag> class CV_EXPORTS VecWriterProxy
{
public:
    VecWriterProxy( FileStorage* _fs ) : fs(_fs) {}
    void operator()(const std::vector<_Tp>& vec) const
    {
        size_t i, count = vec.size();
        for( i = 0; i < count; i++ )
            write( *fs, vec[i] );
    }
    FileStorage* fs;
};

template<typename _Tp> class CV_EXPORTS VecWriterProxy<_Tp,1>
{
public:
    VecWriterProxy( FileStorage* _fs ) : fs(_fs) {}
    void operator()(const std::vector<_Tp>& vec) const
    {
        int _fmt = DataType<_Tp>::fmt;
        char fmt[] = { (char)((_fmt>>8)+'1'), (char)_fmt, '\0' };
        fs->writeRaw( String(fmt), !vec.empty() ? (uchar*)&vec[0] : 0, vec.size()*sizeof(_Tp) );
    }
    FileStorage* fs;
};

template<typename _Tp> static inline void write( FileStorage& fs, const std::vector<_Tp>& vec )
{
    VecWriterProxy<_Tp, DataType<_Tp>::fmt != 0> w(&fs);
    w(vec);
}

template<typename _Tp> static inline void write( FileStorage& fs, const String& name,
                                                const std::vector<_Tp>& vec )
{
    WriteStructContext ws(fs, name, CV_NODE_SEQ+(DataType<_Tp>::fmt != 0 ? CV_NODE_FLOW : 0));
    write(fs, vec);
}

CV_EXPORTS_W void write( FileStorage& fs, const String& name, const Mat& value );
CV_EXPORTS void write( FileStorage& fs, const String& name, const SparseMat& value );

template<typename _Tp> static inline FileStorage& operator << (FileStorage& fs, const _Tp& value)
{
    if( !fs.isOpened() )
        return fs;
    if( fs.state == FileStorage::NAME_EXPECTED + FileStorage::INSIDE_MAP )
        CV_Error( CV_StsError, "No element name has been given" );
    write( fs, fs.elname, value );
    if( fs.state & FileStorage::INSIDE_MAP )
        fs.state = FileStorage::NAME_EXPECTED + FileStorage::INSIDE_MAP;
    return fs;
}

CV_EXPORTS FileStorage& operator << (FileStorage& fs, const String& str);

static inline FileStorage& operator << (FileStorage& fs, const char* str)
{ return (fs << String(str)); }

static inline FileStorage& operator << (FileStorage& fs, char* value)
{ return (fs << String(value)); }

inline FileNode::FileNode() : fs(0), node(0) {}
inline FileNode::FileNode(const CvFileStorage* _fs, const CvFileNode* _node)
    : fs(_fs), node(_node) {}

inline FileNode::FileNode(const FileNode& _node) : fs(_node.fs), node(_node.node) {}

inline int FileNode::type() const { return !node ? NONE : (node->tag & TYPE_MASK); }
inline bool FileNode::empty() const { return node == 0; }
inline bool FileNode::isNone() const { return type() == NONE; }
inline bool FileNode::isSeq() const { return type() == SEQ; }
inline bool FileNode::isMap() const { return type() == MAP; }
inline bool FileNode::isInt() const { return type() == INT; }
inline bool FileNode::isReal() const { return type() == REAL; }
inline bool FileNode::isString() const { return type() == STR; }
inline bool FileNode::isNamed() const { return !node ? false : (node->tag & NAMED) != 0; }
inline size_t FileNode::size() const
{
    int t = type();
    return t == MAP ? (size_t)((CvSet*)node->data.map)->active_count :
        t == SEQ ? (size_t)node->data.seq->total : (size_t)!isNone();
}

inline CvFileNode* FileNode::operator *() { return (CvFileNode*)node; }
inline const CvFileNode* FileNode::operator* () const { return node; }

static inline void read(const FileNode& node, int& value, int default_value)
{
    value = !node.node ? default_value :
    CV_NODE_IS_INT(node.node->tag) ? node.node->data.i :
    CV_NODE_IS_REAL(node.node->tag) ? cvRound(node.node->data.f) : 0x7fffffff;
}

static inline void read(const FileNode& node, bool& value, bool default_value)
{
    int temp; read(node, temp, (int)default_value);
    value = temp != 0;
}

static inline void read(const FileNode& node, uchar& value, uchar default_value)
{
    int temp; read(node, temp, (int)default_value);
    value = saturate_cast<uchar>(temp);
}

static inline void read(const FileNode& node, schar& value, schar default_value)
{
    int temp; read(node, temp, (int)default_value);
    value = saturate_cast<schar>(temp);
}

static inline void read(const FileNode& node, ushort& value, ushort default_value)
{
    int temp; read(node, temp, (int)default_value);
    value = saturate_cast<ushort>(temp);
}

static inline void read(const FileNode& node, short& value, short default_value)
{
    int temp; read(node, temp, (int)default_value);
    value = saturate_cast<short>(temp);
}

static inline void read(const FileNode& node, float& value, float default_value)
{
    value = !node.node ? default_value :
        CV_NODE_IS_INT(node.node->tag) ? (float)node.node->data.i :
        CV_NODE_IS_REAL(node.node->tag) ? (float)node.node->data.f : 1e30f;
}

static inline void read(const FileNode& node, double& value, double default_value)
{
    value = !node.node ? default_value :
        CV_NODE_IS_INT(node.node->tag) ? (double)node.node->data.i :
        CV_NODE_IS_REAL(node.node->tag) ? node.node->data.f : 1e300;
}

static inline void read(const FileNode& node, String& value, const String& default_value)
{
    value = !node.node ? default_value : CV_NODE_IS_STRING(node.node->tag) ? String(node.node->data.str.ptr) : String();
}

CV_EXPORTS_W void read(const FileNode& node, Mat& mat, const Mat& default_mat=Mat() );
CV_EXPORTS void read(const FileNode& node, SparseMat& mat, const SparseMat& default_mat=SparseMat() );

CV_EXPORTS void read(const FileNode& node, std::vector<KeyPoint>& keypoints);
CV_EXPORTS void write(FileStorage& fs, const String& objname, const std::vector<KeyPoint>& keypoints);

inline FileNode::operator int() const
{
    int value;
    read(*this, value, 0);
    return value;
}
inline FileNode::operator float() const
{
    float value;
    read(*this, value, 0.f);
    return value;
}
inline FileNode::operator double() const
{
    double value;
    read(*this, value, 0.);
    return value;
}
inline FileNode::operator String() const
{
    String value;
    read(*this, value, value);
    return value;
}

inline String::String(const FileNode& fn): cstr_(0), len_(0)
{
    read(fn, *this, *this);
}

inline void FileNode::readRaw( const String& fmt, uchar* vec, size_t len ) const
{
    begin().readRaw( fmt, vec, len );
}

template<typename _Tp, int numflag> class CV_EXPORTS VecReaderProxy
{
public:
    VecReaderProxy( FileNodeIterator* _it ) : it(_it) {}
    void operator()(std::vector<_Tp>& vec, size_t count) const
    {
        count = std::min(count, it->remaining);
        vec.resize(count);
        for( size_t i = 0; i < count; i++, ++(*it) )
            read(**it, vec[i], _Tp());
    }
    FileNodeIterator* it;
};

template<typename _Tp> class CV_EXPORTS VecReaderProxy<_Tp,1>
{
public:
    VecReaderProxy( FileNodeIterator* _it ) : it(_it) {}
    void operator()(std::vector<_Tp>& vec, size_t count) const
    {
        size_t remaining = it->remaining, cn = DataType<_Tp>::channels;
        int _fmt = DataType<_Tp>::fmt;
        char fmt[] = { (char)((_fmt>>8)+'1'), (char)_fmt, '\0' };
        size_t remaining1 = remaining/cn;
        count = count < remaining1 ? count : remaining1;
        vec.resize(count);
        it->readRaw( String(fmt), !vec.empty() ? (uchar*)&vec[0] : 0, count*sizeof(_Tp) );
    }
    FileNodeIterator* it;
};

template<typename _Tp> static inline void
read( FileNodeIterator& it, std::vector<_Tp>& vec, size_t maxCount=(size_t)INT_MAX )
{
    VecReaderProxy<_Tp, DataType<_Tp>::fmt != 0> r(&it);
    r(vec, maxCount);
}

template<typename _Tp> static inline void
read( const FileNode& node, std::vector<_Tp>& vec, const std::vector<_Tp>& default_value=std::vector<_Tp>() )
{
    if(!node.node)
        vec = default_value;
    else
    {
        FileNodeIterator it = node.begin();
        read( it, vec );
    }
}

inline FileNodeIterator FileNode::begin() const
{
    return FileNodeIterator(fs, node);
}

inline FileNodeIterator FileNode::end() const
{
    return FileNodeIterator(fs, node, size());
}

inline FileNode FileNodeIterator::operator *() const
{ return FileNode(fs, (const CvFileNode*)reader.ptr); }

inline FileNode FileNodeIterator::operator ->() const
{ return FileNode(fs, (const CvFileNode*)reader.ptr); }

template<typename _Tp> static inline FileNodeIterator& operator >> (FileNodeIterator& it, _Tp& value)
{ read( *it, value, _Tp()); return ++it; }

template<typename _Tp> static inline
FileNodeIterator& operator >> (FileNodeIterator& it, std::vector<_Tp>& vec)
{
    VecReaderProxy<_Tp, DataType<_Tp>::fmt != 0> r(&it);
    r(vec, (size_t)INT_MAX);
    return it;
}

template<typename _Tp> static inline void operator >> (const FileNode& n, _Tp& value)
{ read( n, value, _Tp()); }

template<typename _Tp> static inline void operator >> (const FileNode& n, std::vector<_Tp>& vec)
{ FileNodeIterator it = n.begin(); it >> vec; }

static inline bool operator == (const FileNodeIterator& it1, const FileNodeIterator& it2)
{
    return it1.fs == it2.fs && it1.container == it2.container &&
        it1.reader.ptr == it2.reader.ptr && it1.remaining == it2.remaining;
}

static inline bool operator != (const FileNodeIterator& it1, const FileNodeIterator& it2)
{
    return !(it1 == it2);
}

static inline ptrdiff_t operator - (const FileNodeIterator& it1, const FileNodeIterator& it2)
{
    return it2.remaining - it1.remaining;
}

static inline bool operator < (const FileNodeIterator& it1, const FileNodeIterator& it2)
{
    return it1.remaining > it2.remaining;
}

inline FileNode FileStorage::getFirstTopLevelNode() const
{
    FileNode r = root();
    FileNodeIterator it = r.begin();
    return it != r.end() ? *it : FileNode();
}

//////////////////////////////////////// Various algorithms ////////////////////////////////////

template<typename _Tp> static inline _Tp gcd(_Tp a, _Tp b)
{
    if( a < b )
        std::swap(a, b);
    while( b > 0 )
    {
        _Tp r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// This function splits the input sequence or set into one or more equivalence classes and
// returns the vector of labels - 0-based class indexes for each element.
// predicate(a,b) returns true if the two sequence elements certainly belong to the same class.
//
// The algorithm is described in "Introduction to Algorithms"
// by Cormen, Leiserson and Rivest, the chapter "Data structures for disjoint sets"
template<typename _Tp, class _EqPredicate> int
partition( const std::vector<_Tp>& _vec, std::vector<int>& labels,
           _EqPredicate predicate=_EqPredicate())
{
    int i, j, N = (int)_vec.size();
    const _Tp* vec = &_vec[0];

    const int PARENT=0;
    const int RANK=1;

    std::vector<int> _nodes(N*2);
    int (*nodes)[2] = (int(*)[2])&_nodes[0];

    // The first O(N) pass: create N single-vertex trees
    for(i = 0; i < N; i++)
    {
        nodes[i][PARENT]=-1;
        nodes[i][RANK] = 0;
    }

    // The main O(N^2) pass: merge connected components
    for( i = 0; i < N; i++ )
    {
        int root = i;

        // find root
        while( nodes[root][PARENT] >= 0 )
            root = nodes[root][PARENT];

        for( j = 0; j < N; j++ )
        {
            if( i == j || !predicate(vec[i], vec[j]))
                continue;
            int root2 = j;

            while( nodes[root2][PARENT] >= 0 )
                root2 = nodes[root2][PARENT];

            if( root2 != root )
            {
                // unite both trees
                int rank = nodes[root][RANK], rank2 = nodes[root2][RANK];
                if( rank > rank2 )
                    nodes[root2][PARENT] = root;
                else
                {
                    nodes[root][PARENT] = root2;
                    nodes[root2][RANK] += rank == rank2;
                    root = root2;
                }
                assert( nodes[root][PARENT] < 0 );

                int k = j, parent;

                // compress the path from node2 to root
                while( (parent = nodes[k][PARENT]) >= 0 )
                {
                    nodes[k][PARENT] = root;
                    k = parent;
                }

                // compress the path from node to root
                k = i;
                while( (parent = nodes[k][PARENT]) >= 0 )
                {
                    nodes[k][PARENT] = root;
                    k = parent;
                }
            }
        }
    }

    // Final O(N) pass: enumerate classes
    labels.resize(N);
    int nclasses = 0;

    for( i = 0; i < N; i++ )
    {
        int root = i;
        while( nodes[root][PARENT] >= 0 )
            root = nodes[root][PARENT];
        // re-use the rank as the class label
        if( nodes[root][RANK] >= 0 )
            nodes[root][RANK] = ~nclasses++;
        labels[i] = ~nodes[root][RANK];
    }

    return nclasses;
}


//////////////////////////////////////////////////////////////////////////////

class CV_EXPORTS Formatter
{
public:
    virtual ~Formatter() {}
    virtual void write(std::ostream& out, const Mat& m, const int* params=0, int nparams=0) const = 0;
    virtual void write(std::ostream& out, const void* data, int nelems, int type,
                       const int* params=0, int nparams=0) const = 0;
    static const Formatter* get(const char* fmt="");
    static const Formatter* setDefault(const Formatter* fmt);
};


struct CV_EXPORTS Formatted
{
    Formatted(const Mat& m, const Formatter* fmt,
              const std::vector<int>& params);
    Formatted(const Mat& m, const Formatter* fmt,
              const int* params=0);
    Mat mtx;
    const Formatter* fmt;
    std::vector<int> params;
};

static inline Formatted format(const Mat& mtx, const char* fmt,
                               const std::vector<int>& params=std::vector<int>())
{
    return Formatted(mtx, Formatter::get(fmt), params);
}

template<typename _Tp> static inline Formatted format(const std::vector<Point_<_Tp> >& vec,
                                                      const char* fmt, const std::vector<int>& params=std::vector<int>())
{
    return Formatted(Mat(vec), Formatter::get(fmt), params);
}

template<typename _Tp> static inline Formatted format(const std::vector<Point3_<_Tp> >& vec,
                                                      const char* fmt, const std::vector<int>& params=std::vector<int>())
{
    return Formatted(Mat(vec), Formatter::get(fmt), params);
}

/** \brief prints Mat to the output stream in Matlab notation
 * use like
 @verbatim
 Mat my_mat = Mat::eye(3,3,CV_32F);
 std::cout << my_mat;
 @endverbatim
 */
static inline std::ostream& operator << (std::ostream& out, const Mat& mtx)
{
    Formatter::get()->write(out, mtx);
    return out;
}

/** \brief prints Mat to the output stream allows in the specified notation (see format)
 * use like
 @verbatim
 Mat my_mat = Mat::eye(3,3,CV_32F);
 std::cout << my_mat;
 @endverbatim
 */
static inline std::ostream& operator << (std::ostream& out, const Formatted& fmtd)
{
    fmtd.fmt->write(out, fmtd.mtx);
    return out;
}


template<typename _Tp> static inline std::ostream& operator << (std::ostream& out,
                                                                const std::vector<Point_<_Tp> >& vec)
{
    Formatter::get()->write(out, Mat(vec));
    return out;
}


template<typename _Tp> static inline std::ostream& operator << (std::ostream& out,
                                                                const std::vector<Point3_<_Tp> >& vec)
{
    Formatter::get()->write(out, Mat(vec));
    return out;
}


/** Writes a Matx to an output stream.
 */
template<typename _Tp, int m, int n> inline std::ostream& operator<<(std::ostream& out, const Matx<_Tp, m, n>& matx)
{
    out << cv::Mat(matx);
    return out;
}

/** Writes a point to an output stream in Matlab notation
 */
template<typename _Tp> inline std::ostream& operator<<(std::ostream& out, const Point_<_Tp>& p)
{
    out << "[" << p.x << ", " << p.y << "]";
    return out;
}

/** Writes a point to an output stream in Matlab notation
 */
template<typename _Tp> inline std::ostream& operator<<(std::ostream& out, const Point3_<_Tp>& p)
{
    out << "[" << p.x << ", " << p.y << ", " << p.z << "]";
    return out;
}

/** Writes a Vec to an output stream. Format example : [10, 20, 30]
 */
template<typename _Tp, int n> inline std::ostream& operator<<(std::ostream& out, const Vec<_Tp, n>& vec)
{
    out << "[";

    if(Vec<_Tp, n>::depth < CV_32F)
    {
        for (int i = 0; i < n - 1; ++i) {
            out << (int)vec[i] << ", ";
        }
        out << (int)vec[n-1] << "]";
    }
    else
    {
        for (int i = 0; i < n - 1; ++i) {
            out << vec[i] << ", ";
        }
        out << vec[n-1] << "]";
    }

    return out;
}

/** Writes a Size_ to an output stream. Format example : [640 x 480]
 */
template<typename _Tp> inline std::ostream& operator<<(std::ostream& out, const Size_<_Tp>& size)
{
    out << "[" << size.width << " x " << size.height << "]";
    return out;
}

/** Writes a Rect_ to an output stream. Format example : [640 x 480 from (10, 20)]
 */
template<typename _Tp> inline std::ostream& operator<<(std::ostream& out, const Rect_<_Tp>& rect)
{
    out << "[" << rect.width << " x " << rect.height << " from (" << rect.x << ", " << rect.y << ")]";
    return out;
}


template<typename _Tp> inline Ptr<_Tp> Algorithm::create(const String& name)
{
    return _create(name).ptr<_Tp>();
}

template<typename _Tp>
inline void Algorithm::set(const char* _name, const Ptr<_Tp>& value)
{
    Ptr<Algorithm> algo_ptr = value. template ptr<cv::Algorithm>();
    if (algo_ptr.empty()) {
        CV_Error( CV_StsUnsupportedFormat, "unknown/unsupported Ptr type of the second parameter of the method Algorithm::set");
    }
    info()->set(this, _name, ParamType<Algorithm>::type, &algo_ptr);
}

template<typename _Tp>
inline void Algorithm::set(const String& _name, const Ptr<_Tp>& value)
{
    this->set<_Tp>(_name.c_str(), value);
}

template<typename _Tp>
inline void Algorithm::setAlgorithm(const char* _name, const Ptr<_Tp>& value)
{
    Ptr<Algorithm> algo_ptr = value. template ptr<cv::Algorithm>();
    if (algo_ptr.empty()) {
        CV_Error( CV_StsUnsupportedFormat, "unknown/unsupported Ptr type of the second parameter of the method Algorithm::set");
    }
    info()->set(this, _name, ParamType<Algorithm>::type, &algo_ptr);
}

template<typename _Tp>
inline void Algorithm::setAlgorithm(const String& _name, const Ptr<_Tp>& value)
{
    this->set<_Tp>(_name.c_str(), value);
}

template<typename _Tp> inline typename ParamType<_Tp>::member_type Algorithm::get(const String& _name) const
{
    typename ParamType<_Tp>::member_type value;
    info()->get(this, _name.c_str(), ParamType<_Tp>::type, &value);
    return value;
}

template<typename _Tp> inline typename ParamType<_Tp>::member_type Algorithm::get(const char* _name) const
{
    typename ParamType<_Tp>::member_type value;
    info()->get(this, _name, ParamType<_Tp>::type, &value);
    return value;
}

template<typename _Tp, typename _Base> inline void AlgorithmInfo::addParam(Algorithm& algo, const char* parameter,
                  Ptr<_Tp>& value, bool readOnly, Ptr<_Tp> (Algorithm::*getter)(), void (Algorithm::*setter)(const Ptr<_Tp>&),
                  const String& help)
{
    //TODO: static assert: _Tp inherits from _Base
    addParam_(algo, parameter, ParamType<_Base>::type, &value, readOnly,
              (Algorithm::Getter)getter, (Algorithm::Setter)setter, help);
}

template<typename _Tp> inline void AlgorithmInfo::addParam(Algorithm& algo, const char* parameter,
                  Ptr<_Tp>& value, bool readOnly, Ptr<_Tp> (Algorithm::*getter)(), void (Algorithm::*setter)(const Ptr<_Tp>&),
                  const String& help)
{
    //TODO: static assert: _Tp inherits from Algorithm
    addParam_(algo, parameter, ParamType<Algorithm>::type, &value, readOnly,
              (Algorithm::Getter)getter, (Algorithm::Setter)setter, help);
}

}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif // __cplusplus
#endif
