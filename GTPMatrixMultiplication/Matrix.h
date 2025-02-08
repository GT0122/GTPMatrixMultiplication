#pragma once

#include <cstdint>

class CMatrix
{
public:
	// 기본 생성자
	CMatrix();
	// 복사 생성자
	CMatrix(const CMatrix& matCopy);
	CMatrix(const CMatrix* pMatCopy);
	// 생성자
	// i32Row, i32Column 크기로 Matrix 생성
	CMatrix(int32_t i32Row, int32_t i32Column);
	// pF64Buffer에서 i32Row, i32Column 크기로 Matrix 생성
	CMatrix(double* pF64Buffer, int32_t i32Row, int32_t i32Column);
	// 소멸자
	virtual ~CMatrix();

	// 연산자 오버로딩
	const CMatrix& operator=(const CMatrix& matCopy);
	const CMatrix& operator*=(const CMatrix& matCopy);
	const CMatrix operator*(const CMatrix& matCopy) const;

	// 대입 함수
	bool Assign(const CMatrix& matCopy);
	bool Assign(const CMatrix* pMatCopy);
	// pF64Buffer에서 i32Row, i32Column 크기로 Matrix 할당
	bool Assign(double* pF64Buffer, int32_t i32Row, int32_t i32Column);

	// 초기화
	bool Clear();

	// i32Row, i32Column 크기로 Matrix 생성, bFillZero 가 true일 경우 0으로 초기화
	bool Create(int32_t i32Row, int32_t i32Column, bool bFillZero = true);

	// i32Row, i32Column 위치에 f64Value값 설정
	bool SetValue(double f64Value, int32_t i32Row, int32_t i32Column);
	// i32Row, i32Column 위치의 값을 f64Value에 반환
	bool GetValue(double& f64Value, int32_t i32Row, int32_t i32Column) const;
	bool GetValue(double* pF64Value, int32_t i32Row, int32_t i32Column) const;

	int32_t GetRow() const;
	int32_t GetColumn() const;
	const double* GetBuffer() const;

	// 연산 결과를 this에 반환
	bool Multiply(const CMatrix& matOperand);
	// 연산 결과를 pMatResult에 반환
	bool Multiply(const CMatrix& matOperand, CMatrix* pMatResult) const;

protected:
	int32_t m_i32Row;
	int32_t m_i32Column;
	double* m_pF64Buffer;
};