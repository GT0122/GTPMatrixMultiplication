#pragma once

#include <cstdint>

class CMatrix
{
public:
	// �⺻ ������
	CMatrix();
	// ���� ������
	CMatrix(const CMatrix& matCopy);
	CMatrix(const CMatrix* pMatCopy);
	// ������
	// i32Row, i32Column ũ��� Matrix ����
	CMatrix(int32_t i32Row, int32_t i32Column);
	// pF64Buffer���� i32Row, i32Column ũ��� Matrix ����
	CMatrix(double* pF64Buffer, int32_t i32Row, int32_t i32Column);
	// �Ҹ���
	virtual ~CMatrix();

	// ������ �����ε�
	const CMatrix& operator=(const CMatrix& matCopy);
	const CMatrix& operator*=(const CMatrix& matCopy);
	const CMatrix operator*(const CMatrix& matCopy) const;

	// ���� �Լ�
	bool Assign(const CMatrix& matCopy);
	bool Assign(const CMatrix* pMatCopy);
	// pF64Buffer���� i32Row, i32Column ũ��� Matrix �Ҵ�
	bool Assign(double* pF64Buffer, int32_t i32Row, int32_t i32Column);

	// �ʱ�ȭ
	bool Clear();

	// i32Row, i32Column ũ��� Matrix ����, bFillZero �� true�� ��� 0���� �ʱ�ȭ
	bool Create(int32_t i32Row, int32_t i32Column, bool bFillZero = true);

	// i32Row, i32Column ��ġ�� f64Value�� ����
	bool SetValue(double f64Value, int32_t i32Row, int32_t i32Column);
	// i32Row, i32Column ��ġ�� ���� f64Value�� ��ȯ
	bool GetValue(double& f64Value, int32_t i32Row, int32_t i32Column) const;
	bool GetValue(double* pF64Value, int32_t i32Row, int32_t i32Column) const;

	int32_t GetRow() const;
	int32_t GetColumn() const;
	const double* GetBuffer() const;

	// ���� ����� this�� ��ȯ
	bool Multiply(const CMatrix& matOperand);
	// ���� ����� pMatResult�� ��ȯ
	bool Multiply(const CMatrix& matOperand, CMatrix* pMatResult) const;

protected:
	int32_t m_i32Row;
	int32_t m_i32Column;
	double* m_pF64Buffer;
};