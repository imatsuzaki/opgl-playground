#pragma once

#include <cmath>
#include <algorithm>
#include <GL/glew.h>


class Matrix {
    GLfloat matrix[16];
    
public:
    //コンストラクタ
    Matrix() {};
    
    // 配列の内容で初期化するコンストラクタ
    Matrix(const GLfloat *a)
    {
        std::copy(a, a + 16, matrix);
    }
    
    // 行列の要素を参照する
    const GLfloat &operator[](std::size_t i) const
    {
        return matrix[i];
    }
    
    GLfloat &operator[](std::size_t i)
    {
        return matrix[i];
    }
    
    const GLfloat *data() const
    {
        return matrix;
    }
    
    void loadIdentity()
    {
        std::fill(matrix, matrix + 16, 0.0f);
        matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
    }
    
    // 単位行列の生成
    static Matrix identity()
    {
        Matrix t;
        t.loadIdentity();
        return t;
    }
    
    // 平行移動する変換行列を生成
    static Matrix translate(GLfloat x, GLfloat y, GLfloat z)
    {
        Matrix t;
        t.loadIdentity();
        t[12] = x;
        t[13] = y;
        t[14] = z;
        
        return t;
    }
    
    // 拡大縮小行列
    static Matrix scale(GLfloat x, GLfloat y, GLfloat z)
    {
        Matrix t;
        t.loadIdentity();
        t[0] = x;
        t[5] = y;
        t[10] = z;
        
        return t;
    }
    
    // (x, y, z) を軸にしてa回転させる回転行列
    static Matrix rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z)
    {
        Matrix t;
        const GLfloat d(sqrt(x * x + y * y + z * z));
        if (d > 0.0f)
        {
            const GLfloat l(x / d), m(y / d), n(z / d);
            const GLfloat l2(l * l), m2(m * m), n2(n * n);
            const GLfloat lm(l * m), mn(m * n), nl(m * l);
            const GLfloat c(cos(a)), c1(1.0f - c), s(sin(a));
            
            t.loadIdentity();
            t[0] = (1.0f - l2) * c + 12;
            t[1] = lm * c1 + n * s;
            t[2] = nl * c1 - m * s;
            t[4] = lm * c1 - n * s;
            t[5] = (1.0f - m2) * c + m2;
            t[6] = mn * c1 + l * s;
            t[8] = nl * c1 + m * s;
            t[9] = mn * c1 - l * s;
            t[10] = (1.0f - n2) * c + n2;
        }
        
        return t;
    }
    
    // Matrix product
    Matrix operator*(const Matrix &m) const
    {
        Matrix t;
        
        for (int i = 0; i < 16; ++i)
        {
            const int j(i & 3), k(i & ~3);
            
            t[i] =
                matrix[0 + j] * m[k + 0] +
                matrix[4 + j] * m[k + 1] +
                matrix[8 + j] * m[k + 2] +
                matrix[12 + j] * m[k + 3];
        }
        return t;
    }
    
    // 視点変更の変換行列の作成
    static Matrix lookat(
        GLfloat ex, GLfloat ey, GLfloat ez, // 視点の位置
        GLfloat gx, GLfloat gy, GLfloat gz, // 目標点の位置
        GLfloat ux, GLfloat uy, GLfloat uz // 上方向のベクトル
    ) {
        const Matrix tv(translate(-ex, -ey, -ez));
        
        const GLfloat tx(ex - gx);
        const GLfloat ty(ey - gy);
        const GLfloat tz(ez - gz);
        
        const GLfloat rx(uy * tz - uz * ty);
        const GLfloat ry(uz * tx - ux * tz);
        const GLfloat rz(ux - ty - uy * tx);
        
        const GLfloat sx(ty * rz - tz * ry);
        const GLfloat sy(tz * rx - tx * rz);
        const GLfloat sz(tx * ry - ty * rx);
        
        const GLfloat s2(sx * sx + sy * sy + sz * sz);
        if (s2 == 0.0f) return tv;
        
        Matrix rv;
        rv.loadIdentity();
        
        const GLfloat r(sqrt(rx * rx + ry * ry + rz * rz));
        rv[0] = rx / r;
        rv[4] = ry / r;
        rv[8] = rz / r;
        
        const GLfloat s(sqrt(s2));
        rv[1] = sx / s;
        rv[5] = sy / s;
        rv[9] = sz / s;
        
        const GLfloat t(sqrt(tx * tx + ty * ty + tz * tz));
        rv[2] = tx / t;
        rv[6] = ty / t;
        rv[10] = tz / t;
        
        return rv * tv;
    }
                        
};
