#include "Matrix.h"
#include <immintrin.h>
#include <cstring>
#include <utility>

CMatrix::CMatrix()
{
	m_i32Row = 0;
	m_i32Column = 0;
	m_pF64Buffer = nullptr;
}

CMatrix::CMatrix(const CMatrix& matCopy)
{
	m_i32Row = matCopy.GetRow();
	m_i32Column = matCopy.GetColumn();
	m_pF64Buffer = new double[m_i32Row * m_i32Column];
	memcpy(m_pF64Buffer, matCopy.m_pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);
}

CMatrix::CMatrix(const CMatrix* pMatCopy)
{
	if(pMatCopy)
	{
		m_i32Row = pMatCopy->GetRow();
		m_i32Column = pMatCopy->GetColumn();
		m_pF64Buffer = new double[m_i32Row * m_i32Column];
		memcpy(m_pF64Buffer, pMatCopy->m_pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);
	}
	else
	{
		m_i32Row = 0;
		m_i32Column = 0;
		m_pF64Buffer = nullptr;
	}
}

CMatrix::CMatrix(int32_t i32Row, int32_t i32Column)
{
	if(i32Row > 0 && i32Column > 0)
	{
		m_i32Row = i32Row;
		m_i32Column = i32Column;
		m_pF64Buffer = new double[m_i32Row * m_i32Column];
	}
	else
	{
		m_i32Row = 0;
		m_i32Column = 0;
		m_pF64Buffer = nullptr;
	}
}

CMatrix::CMatrix(double* pF64Buffer, int32_t i32Row, int32_t i32Column)
{
	if(i32Row > 0 && i32Column > 0 && pF64Buffer)
	{
		m_i32Row = i32Row;
		m_i32Column = i32Column;
		m_pF64Buffer = new double[m_i32Row * m_i32Column];
		memcpy(m_pF64Buffer, pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);
	}
	else
	{
		m_i32Row = 0;
		m_i32Column = 0;
		m_pF64Buffer = nullptr;
	}
}

CMatrix::~CMatrix()
{
	m_i32Row = 0;
	m_i32Column = 0;

	if(m_pF64Buffer)
		delete m_pF64Buffer;

	m_pF64Buffer = nullptr;
}

const CMatrix& CMatrix::operator=(const CMatrix& matCopy)
{
	// TODO: 여기에 return 문을 삽입합니다.
	do
	{
		if(matCopy.GetRow() < 0 || matCopy.GetColumn() < 0)
			break;

		m_i32Row = matCopy.GetRow();
		m_i32Column = matCopy.GetColumn();

		if(m_pF64Buffer)
			delete m_pF64Buffer;
		
		if(m_i32Row == 0 || m_i32Column == 0)
			m_pF64Buffer = nullptr;
		else
		{
			m_pF64Buffer = new double[m_i32Row * m_i32Column];
			memcpy(m_pF64Buffer, matCopy.m_pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);
		}
	}
	while(false);

	return *this;
}

const CMatrix& CMatrix::operator*=(const CMatrix& matCopy)
{
	// TODO: 여기에 return 문을 삽입합니다.
	do
	{
		if(m_i32Row <= 0 || m_i32Column <= 0 || matCopy.GetRow() <= 0 || matCopy.GetColumn() <= 0)
		{
			Clear();
			break;
		}

		if(m_i32Column != matCopy.GetRow())
			Clear();
		else
		{
			bool bTemp = Multiply(matCopy);

			if(!bTemp)
				Clear();
		}
	}
	while(false);

	return *this;
}

const CMatrix CMatrix::operator*(const CMatrix& matCopy) const
{
	CMatrix matTemp = CMatrix();

	do
	{
		if(m_i32Row <= 0 || m_i32Column <= 0 || matCopy.GetRow() <= 0 || matCopy.GetColumn() <= 0)
		{
			matTemp.Clear();
			break;
		}

		if(m_i32Column == matCopy.m_i32Row)
		{
			bool bTemp = Multiply(matCopy, &matTemp);

			if(!bTemp)
				matTemp.Clear();
		}
		else
			matTemp.Clear();
	}
	while(false);

	return matTemp;
}

bool CMatrix::Assign(const CMatrix& matCopy)
{
	bool bChange = false;

	do
	{
		if(matCopy.GetRow() <= 0 || matCopy.GetColumn() <= 0)
			break;

		m_i32Row = matCopy.GetRow();
		m_i32Column = matCopy.GetColumn();

		if(m_pF64Buffer)
			delete m_pF64Buffer;

		m_pF64Buffer = new double[m_i32Row * m_i32Column];
		memcpy(m_pF64Buffer, matCopy.m_pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);

		bChange = true;
	}
	while(false);

	return bChange;
}

bool CMatrix::Assign(const CMatrix* pMatCopy)
{
	bool bChange = false;

	do
	{
		if(pMatCopy->GetRow() <= 0 || pMatCopy->GetColumn() <= 0 || !pMatCopy)
			break;

		m_i32Row = pMatCopy->GetRow();
		m_i32Column = pMatCopy->GetColumn();

		if(m_pF64Buffer)
			delete m_pF64Buffer;

		m_pF64Buffer = new double[m_i32Row * m_i32Column];
		memcpy(m_pF64Buffer, pMatCopy->m_pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);

		bChange = true;
	}
	while(false);

	return bChange;
}

bool CMatrix::Assign(double* pF64Buffer, int32_t i32Row, int32_t i32Column)
{
	bool bChange = false;

	do
	{
		if(i32Row <= 0 || i32Column <= 0 || !pF64Buffer)
			break;

		m_i32Row = i32Row;
		m_i32Column = i32Column;

		if(m_pF64Buffer)
			delete m_pF64Buffer;

		m_pF64Buffer = new double[m_i32Row * m_i32Column];
		memcpy(m_pF64Buffer, pF64Buffer, sizeof(double) * m_i32Row * m_i32Column);

		bChange = true;
	}
	while(false);

	return bChange;
}

bool CMatrix::Clear()
{
	bool bClear = false;

	do
	{
		m_i32Row = 0;
		m_i32Column = 0;

		if(m_pF64Buffer)
			delete m_pF64Buffer;

		m_pF64Buffer = nullptr;

		bClear = true;
	}
	while(false);

	return bClear;
}

bool CMatrix::Create(int32_t i32Row, int32_t i32Column, bool bFillZero)
{
	bool bChange = false;

	do
	{
		if(i32Row <= 0 || i32Column <= 0)
			break;

		m_i32Row = i32Row;
		m_i32Column = i32Column;

		if(m_pF64Buffer)
			delete m_pF64Buffer;

		if(bFillZero)
			m_pF64Buffer = new double[m_i32Row * m_i32Column]();
		else
			m_pF64Buffer = new double[m_i32Row * m_i32Column];

		bChange = true;
	}
	while(false);

	return bChange;
}

bool CMatrix::SetValue(double f64Value, int32_t i32Row, int32_t i32Column)
{
	bool bChange = false;

	do
	{
		if(i32Row < 0 || i32Row > m_i32Row || i32Column < 0 || i32Column > m_i32Column)
			break;

		m_pF64Buffer[i32Row * m_i32Column + i32Column] = f64Value;

		bChange = true;
	}
	while(false);

	return bChange;
}

bool CMatrix::GetValue(double& f64Value, int32_t i32Row, int32_t i32Column) const
{
	bool bChange = false;

	do
	{
		if(i32Row < 0 || i32Row > m_i32Row || i32Column < 0 || i32Column > m_i32Column)
			break;

		f64Value = m_pF64Buffer[i32Row * m_i32Column + i32Column];

		bChange = true;
	}
	while(false);

	return bChange;
}

bool CMatrix::GetValue(double* pF64Value, int32_t i32Row, int32_t i32Column) const
{
	bool bChange = false;

	do
	{
		if(i32Row < 0 || i32Row > m_i32Row || i32Column < 0 || i32Column > m_i32Column || !pF64Value)
			break;

		*pF64Value = m_pF64Buffer[i32Row * m_i32Column + i32Column];

		bChange = true;
	}
	while(false);

	return bChange;
}

int32_t CMatrix::GetRow() const
{
	return m_i32Row;
}

int32_t CMatrix::GetColumn() const
{
	return m_i32Column;
}

const double* CMatrix::GetBuffer() const
{
	return m_pF64Buffer;
}

bool CMatrix::Multiply(const CMatrix& matOperand)
{
	bool bMul = false;

	do
	{
		if(m_i32Column != matOperand.GetRow() || m_pF64Buffer == nullptr || matOperand.GetBuffer() == nullptr)
			break;

		__m256d* pM256dMatrix1 = (__m256d*)malloc(sizeof(__m256d) * m_i32Row * (m_i32Column / 4 + 1));
		__m256d* pM256dMatrix2 = (__m256d*)malloc(sizeof(__m256d) * (matOperand.m_i32Row / 4 + 1) * matOperand.m_i32Column);
		double* pF64Result = new double[m_i32Row * matOperand.m_i32Column]();

		if(pM256dMatrix1 == NULL || pM256dMatrix2 == NULL)
			break;

		int32_t i32RBlock = 256, i32CBlock = 16;

		__m256d arrM256dMul[16] = { 0 };
		__m256d arrM256dNum0[16] = { 0 };
		__m256d arrM256dNum1[16] = { 0 };
		__m128d arrM128dNum2[16] = { 0 };
		__m256d arrM256dNum2[16] = { 0 };

		double arrF64Temp[16] = { 0 };

		for(int32_t i32Row = 0; i32Row < m_i32Row; i32Row++)
		{
			for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
				pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index] = _mm256_setr_pd(m_pF64Buffer[i32Row * m_i32Column + i32Index * 4], m_pF64Buffer[i32Row * m_i32Column + i32Index * 4 + 1], m_pF64Buffer[i32Row * m_i32Column + i32Index * 4 + 2], m_pF64Buffer[i32Row * m_i32Column + i32Index * 4 + 3]);
		}

		for(int32_t i32Column = 0; i32Column < matOperand.m_i32Column; i32Column++)
		{
			for(int32_t i32Index = 0; i32Index < matOperand.m_i32Row / 4; i32Index++)
				pM256dMatrix2[i32Column * (matOperand.m_i32Row / 4) + i32Index] = _mm256_setr_pd(matOperand.GetBuffer()[i32Index * 4 * matOperand.m_i32Column + i32Column], matOperand.GetBuffer()[(i32Index * 4 + 1) * matOperand.m_i32Column + i32Column], matOperand.GetBuffer()[(i32Index * 4 + 2) * matOperand.m_i32Column + i32Column], matOperand.GetBuffer()[(i32Index * 4 + 3) * matOperand.m_i32Column + i32Column]);
		}

		for(int32_t i32Rows = 0; i32Rows < m_i32Row; i32Rows += i32RBlock)
		{
			for(int32_t i32Columns = 0; i32Columns < (matOperand.m_i32Column / 16) * 16; i32Columns += i32CBlock)
			{
				for(int32_t i32Row = i32Rows; i32Row < std::min(m_i32Row, i32Rows + i32RBlock); i32Row++)
				{
					for(int32_t i32Column = i32Columns; i32Column < std::min((matOperand.m_i32Column / 16) * 16, i32Columns + i32CBlock); i32Column += 16)
					{
						for(int32_t i32Index = 0; i32Index < 16; i32Index += 8)
						{
							arrM256dNum0[i32Index] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 1] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 2] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 3] = _mm256_setzero_pd();

							arrM256dNum0[i32Index + 4] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 5] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 6] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 7] = _mm256_setzero_pd();
						}

						__m256d* m256dCur = nullptr;

						for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
						{
							__m256d m256dTemp = pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index];

							arrM256dMul[0] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[i32Column * (m_i32Column / 4) + i32Index]);
							arrM256dMul[1] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 1) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[2] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 2) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[3] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 3) * (m_i32Column / 4) + i32Index]);

							arrM256dMul[4] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 4) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[5] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 5) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[6] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 6) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[7] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 7) * (m_i32Column / 4) + i32Index]);

							arrM256dNum0[0] = _mm256_add_pd(arrM256dNum0[0], arrM256dMul[0]);
							arrM256dNum0[1] = _mm256_add_pd(arrM256dNum0[1], arrM256dMul[1]);
							arrM256dNum0[2] = _mm256_add_pd(arrM256dNum0[2], arrM256dMul[2]);
							arrM256dNum0[3] = _mm256_add_pd(arrM256dNum0[3], arrM256dMul[3]);

							arrM256dNum0[4] = _mm256_add_pd(arrM256dNum0[4], arrM256dMul[4]);
							arrM256dNum0[5] = _mm256_add_pd(arrM256dNum0[5], arrM256dMul[5]);
							arrM256dNum0[6] = _mm256_add_pd(arrM256dNum0[6], arrM256dMul[6]);
							arrM256dNum0[7] = _mm256_add_pd(arrM256dNum0[7], arrM256dMul[7]);
						}

						for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
						{
							__m256d m256dTemp = pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index];

							arrM256dMul[8] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 8) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[9] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 9) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[10] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 10) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[11] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 11) * (m_i32Column / 4) + i32Index]);

							arrM256dMul[12] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 12) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[13] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 13) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[14] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 14) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[15] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 15) * (m_i32Column / 4) + i32Index]);

							arrM256dNum0[8] = _mm256_add_pd(arrM256dNum0[8], arrM256dMul[8]);
							arrM256dNum0[9] = _mm256_add_pd(arrM256dNum0[9], arrM256dMul[9]);
							arrM256dNum0[10] = _mm256_add_pd(arrM256dNum0[10], arrM256dMul[10]);
							arrM256dNum0[11] = _mm256_add_pd(arrM256dNum0[11], arrM256dMul[11]);

							arrM256dNum0[12] = _mm256_add_pd(arrM256dNum0[12], arrM256dMul[12]);
							arrM256dNum0[13] = _mm256_add_pd(arrM256dNum0[13], arrM256dMul[13]);
							arrM256dNum0[14] = _mm256_add_pd(arrM256dNum0[14], arrM256dMul[14]);
							arrM256dNum0[15] = _mm256_add_pd(arrM256dNum0[15], arrM256dMul[15]);
						}

						__m256d arrM256dTemp[2];

						for(int32_t i32Index = 0; i32Index < 16; i32Index += 8)
						{
							arrM256dNum1[i32Index] = _mm256_hadd_pd(arrM256dNum0[i32Index], arrM256dNum0[i32Index]);
							arrM256dNum2[i32Index] = _mm256_add_pd(arrM256dNum1[i32Index], _mm256_permute2f128_pd(arrM256dNum1[i32Index], arrM256dNum1[i32Index], 1));
							arrM256dNum1[i32Index + 1] = _mm256_hadd_pd(arrM256dNum0[i32Index + 1], arrM256dNum0[i32Index + 1]);
							arrM256dNum2[i32Index + 1] = _mm256_add_pd(arrM256dNum1[i32Index + 1], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 1], arrM256dNum1[i32Index + 1], 1));
							arrM256dNum1[i32Index + 2] = _mm256_hadd_pd(arrM256dNum0[i32Index + 2], arrM256dNum0[i32Index + 2]);
							arrM256dNum2[i32Index + 2] = _mm256_add_pd(arrM256dNum1[i32Index + 2], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 2], arrM256dNum1[i32Index + 2], 1));
							arrM256dNum1[i32Index + 3] = _mm256_hadd_pd(arrM256dNum0[i32Index + 3], arrM256dNum0[i32Index + 3]);
							arrM256dNum2[i32Index + 3] = _mm256_add_pd(arrM256dNum1[i32Index + 3], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 3], arrM256dNum1[i32Index + 3], 1));

							arrM256dNum1[i32Index + 4] = _mm256_hadd_pd(arrM256dNum0[i32Index + 4], arrM256dNum0[i32Index + 4]);
							arrM256dNum2[i32Index + 4] = _mm256_add_pd(arrM256dNum1[i32Index + 4], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 4], arrM256dNum1[i32Index + 4], 1));
							arrM256dNum1[i32Index + 5] = _mm256_hadd_pd(arrM256dNum0[i32Index + 5], arrM256dNum0[i32Index + 5]);
							arrM256dNum2[i32Index + 5] = _mm256_add_pd(arrM256dNum1[i32Index + 5], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 5], arrM256dNum1[i32Index + 5], 1));
							arrM256dNum1[i32Index + 6] = _mm256_hadd_pd(arrM256dNum0[i32Index + 6], arrM256dNum0[i32Index + 6]);
							arrM256dNum2[i32Index + 6] = _mm256_add_pd(arrM256dNum1[i32Index + 6], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 6], arrM256dNum1[i32Index + 6], 1));
							arrM256dNum1[i32Index + 7] = _mm256_hadd_pd(arrM256dNum0[i32Index + 7], arrM256dNum0[i32Index + 7]);
							arrM256dNum2[i32Index + 7] = _mm256_add_pd(arrM256dNum1[i32Index + 7], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 7], arrM256dNum1[i32Index + 7], 1));

							arrM256dTemp[0] = _mm256_setr_pd(_mm256_cvtsd_f64(arrM256dNum2[i32Index]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 1]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 2]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 3]));
							arrM256dTemp[1] = _mm256_setr_pd(_mm256_cvtsd_f64(arrM256dNum2[i32Index + 4]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 5]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 6]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 7]));

							memcpy(&arrF64Temp[i32Index], &arrM256dTemp, sizeof(double) * 8);
						}

						if(m_i32Column % 4 > 0)
						{
							for(int32_t i32Index = (m_i32Column / 4) * 4; i32Index < m_i32Column; i32Index++)
							{
								double f64Temp = m_pF64Buffer[i32Row * m_i32Column + i32Index];

								arrF64Temp[0] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column];
								arrF64Temp[1] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 1];
								arrF64Temp[2] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 2];
								arrF64Temp[3] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 3];

								arrF64Temp[4] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 4];
								arrF64Temp[5] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 5];
								arrF64Temp[6] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 6];
								arrF64Temp[7] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 7];
							}

							for(int32_t i32Index = (m_i32Column / 4) * 4; i32Index < m_i32Column; i32Index++)
							{
								double f64Temp = m_pF64Buffer[i32Row * m_i32Column + i32Index];

								arrF64Temp[8] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 8];
								arrF64Temp[9] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 9];
								arrF64Temp[10] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 10];
								arrF64Temp[11] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 11];

								arrF64Temp[12] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 12];
								arrF64Temp[13] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 13];
								arrF64Temp[14] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 14];
								arrF64Temp[15] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 15];
							}
						}

						memcpy(&pF64Result[i32Row * matOperand.m_i32Column + i32Column], arrF64Temp, sizeof(double) * 16);
					}
				}
			}
		}

		if(matOperand.m_i32Column % 16 > 0)
		{
			for(int32_t i32Row = 0; i32Row < m_i32Row; i32Row++)
			{
				for(int32_t i32Column = (matOperand.m_i32Column / 16) * 16; i32Column < matOperand.m_i32Column; i32Column++)
				{
					arrM256dNum0[0] = _mm256_setzero_pd();

					for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
					{
						arrM256dMul[0] = _mm256_mul_pd(pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index], pM256dMatrix2[i32Column * (matOperand.m_i32Row / 4) + i32Index]);

						arrM256dNum0[0] = _mm256_add_pd(arrM256dNum0[0], arrM256dMul[0]);
					}

					arrM256dNum1[0] = _mm256_hadd_pd(arrM256dNum0[0], arrM256dNum0[0]);
					arrM128dNum2[0] = _mm_add_pd(_mm256_extractf128_pd(arrM256dNum1[0], 0), _mm256_extractf128_pd(arrM256dNum1[0], 1));

					arrF64Temp[0] = _mm_cvtsd_f64(arrM128dNum2[0]);

					if(m_i32Column % 4 > 0)
					{
						for(int32_t i32Index = (m_i32Column / 4) * 4; i32Index < m_i32Column; i32Index++)
							arrF64Temp[0] += m_pF64Buffer[i32Row * m_i32Column + i32Index] * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column];
					}

					memcpy(&pF64Result[i32Row * matOperand.m_i32Column + i32Column], arrF64Temp, sizeof(double));
				}
			}
		}

		free(pM256dMatrix1);
		free(pM256dMatrix2);

		if(m_pF64Buffer)
			delete[] m_pF64Buffer;

		m_i32Column = matOperand.m_i32Column;
		m_pF64Buffer = new double[m_i32Row * matOperand.m_i32Column];

		memcpy(m_pF64Buffer, pF64Result, sizeof(double) * m_i32Row * matOperand.m_i32Column);

		delete[] pF64Result;

		bMul = true;
	}
	while(false);

	return bMul;
}

bool CMatrix::Multiply(const CMatrix& matOperand, CMatrix* pMatResult) const
{
	bool bMul = false;

	do
	{
		if(m_i32Column != matOperand.GetRow() || !pMatResult || m_pF64Buffer == nullptr || matOperand.GetBuffer() == nullptr)
			break;

		pMatResult->m_i32Row = m_i32Row;
		pMatResult->m_i32Column = matOperand.GetColumn();

		if(pMatResult->m_pF64Buffer)
			delete pMatResult->m_pF64Buffer;

		pMatResult->m_pF64Buffer = new double[m_i32Row * matOperand.GetColumn()]();

		__m256d* pM256dMatrix1 = (__m256d*)malloc(sizeof(__m256d) * m_i32Row * (m_i32Column / 4 + 1));
		__m256d* pM256dMatrix2 = (__m256d*)malloc(sizeof(__m256d) * (matOperand.m_i32Row / 4 + 1) * matOperand.m_i32Column);
		
		int32_t i32RBlock = 256, i32CBlock = 16;

		__m256d arrM256dMul[16] = { 0 };
		__m256d arrM256dNum0[16] = { 0 };
		__m256d arrM256dNum1[16] = { 0 };
		__m128d arrM128dNum2[16] = { 0 };
		__m256d arrM256dNum2[16] = { 0 };

		double arrF64Temp[16] = { 0 };

		for(int32_t i32Row = 0; i32Row < m_i32Row; i32Row++)
		{
			for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
				pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index] = _mm256_setr_pd(m_pF64Buffer[i32Row * m_i32Column + i32Index * 4], m_pF64Buffer[i32Row * m_i32Column + i32Index * 4 + 1], m_pF64Buffer[i32Row * m_i32Column + i32Index * 4 + 2], m_pF64Buffer[i32Row * m_i32Column + i32Index * 4 + 3]);
		}

		for(int32_t i32Column = 0; i32Column < matOperand.m_i32Column; i32Column++)
		{
			for(int32_t i32Index = 0; i32Index < matOperand.m_i32Row / 4; i32Index++)
				pM256dMatrix2[i32Column * (matOperand.m_i32Row / 4) + i32Index] = _mm256_setr_pd(matOperand.GetBuffer()[i32Index * 4 * matOperand.m_i32Column + i32Column], matOperand.GetBuffer()[(i32Index * 4 + 1) * matOperand.m_i32Column + i32Column], matOperand.GetBuffer()[(i32Index * 4 + 2) * matOperand.m_i32Column + i32Column], matOperand.GetBuffer()[(i32Index * 4 + 3) * matOperand.m_i32Column + i32Column]);
		}

		for(int32_t i32Rows = 0; i32Rows < m_i32Row; i32Rows += i32RBlock)
		{
			for(int32_t i32Columns = 0; i32Columns < (matOperand.m_i32Column / 16) * 16; i32Columns += i32CBlock)
			{
				for(int32_t i32Row = i32Rows; i32Row < std::min(m_i32Row, i32Rows + i32RBlock); i32Row++)
				{
					for(int32_t i32Column = i32Columns; i32Column < std::min((matOperand.m_i32Column / 16) * 16, i32Columns + i32CBlock); i32Column += 16)
					{
						for(int32_t i32Index = 0; i32Index < 16; i32Index += 8)
						{
							arrM256dNum0[i32Index] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 1] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 2] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 3] = _mm256_setzero_pd();

							arrM256dNum0[i32Index + 4] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 5] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 6] = _mm256_setzero_pd();
							arrM256dNum0[i32Index + 7] = _mm256_setzero_pd();
						}

						__m256d* m256dCur = nullptr;

						for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
						{
							__m256d m256dTemp = pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index];

							arrM256dMul[0] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[i32Column * (m_i32Column / 4) + i32Index]);
							arrM256dMul[1] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 1) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[2] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 2) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[3] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 3) * (m_i32Column / 4) + i32Index]);

							arrM256dMul[4] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 4) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[5] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 5) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[6] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 6) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[7] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 7) * (m_i32Column / 4) + i32Index]);

							arrM256dNum0[0] = _mm256_add_pd(arrM256dNum0[0], arrM256dMul[0]);
							arrM256dNum0[1] = _mm256_add_pd(arrM256dNum0[1], arrM256dMul[1]);
							arrM256dNum0[2] = _mm256_add_pd(arrM256dNum0[2], arrM256dMul[2]);
							arrM256dNum0[3] = _mm256_add_pd(arrM256dNum0[3], arrM256dMul[3]);

							arrM256dNum0[4] = _mm256_add_pd(arrM256dNum0[4], arrM256dMul[4]);
							arrM256dNum0[5] = _mm256_add_pd(arrM256dNum0[5], arrM256dMul[5]);
							arrM256dNum0[6] = _mm256_add_pd(arrM256dNum0[6], arrM256dMul[6]);
							arrM256dNum0[7] = _mm256_add_pd(arrM256dNum0[7], arrM256dMul[7]);
						}
						
						for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
						{
							__m256d m256dTemp = pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index];

							arrM256dMul[8] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 8) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[9] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 9) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[10] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 10) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[11] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 11) * (m_i32Column / 4) + i32Index]);

							arrM256dMul[12] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 12) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[13] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 13) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[14] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 14) * (m_i32Column / 4) + i32Index]);
							arrM256dMul[15] = _mm256_mul_pd(m256dTemp, pM256dMatrix2[(i32Column + 15) * (m_i32Column / 4) + i32Index]);

							arrM256dNum0[8] = _mm256_add_pd(arrM256dNum0[8], arrM256dMul[8]);
							arrM256dNum0[9] = _mm256_add_pd(arrM256dNum0[9], arrM256dMul[9]);
							arrM256dNum0[10] = _mm256_add_pd(arrM256dNum0[10], arrM256dMul[10]);
							arrM256dNum0[11] = _mm256_add_pd(arrM256dNum0[11], arrM256dMul[11]);

							arrM256dNum0[12] = _mm256_add_pd(arrM256dNum0[12], arrM256dMul[12]);
							arrM256dNum0[13] = _mm256_add_pd(arrM256dNum0[13], arrM256dMul[13]);
							arrM256dNum0[14] = _mm256_add_pd(arrM256dNum0[14], arrM256dMul[14]);
							arrM256dNum0[15] = _mm256_add_pd(arrM256dNum0[15], arrM256dMul[15]);
						}

						__m256d arrM256dTemp[2];

						for(int32_t i32Index = 0; i32Index < 16; i32Index +=8)
						{
							arrM256dNum1[i32Index] = _mm256_hadd_pd(arrM256dNum0[i32Index], arrM256dNum0[i32Index]);
							arrM256dNum2[i32Index] = _mm256_add_pd(arrM256dNum1[i32Index], _mm256_permute2f128_pd(arrM256dNum1[i32Index], arrM256dNum1[i32Index], 1));
							arrM256dNum1[i32Index + 1] = _mm256_hadd_pd(arrM256dNum0[i32Index + 1], arrM256dNum0[i32Index + 1]);
							arrM256dNum2[i32Index + 1] = _mm256_add_pd(arrM256dNum1[i32Index + 1], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 1], arrM256dNum1[i32Index + 1], 1));
							arrM256dNum1[i32Index + 2] = _mm256_hadd_pd(arrM256dNum0[i32Index + 2], arrM256dNum0[i32Index + 2]);
							arrM256dNum2[i32Index + 2] = _mm256_add_pd(arrM256dNum1[i32Index + 2], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 2], arrM256dNum1[i32Index + 2], 1));
							arrM256dNum1[i32Index + 3] = _mm256_hadd_pd(arrM256dNum0[i32Index + 3], arrM256dNum0[i32Index + 3]);
							arrM256dNum2[i32Index + 3] = _mm256_add_pd(arrM256dNum1[i32Index + 3], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 3], arrM256dNum1[i32Index + 3], 1));

							arrM256dNum1[i32Index + 4] = _mm256_hadd_pd(arrM256dNum0[i32Index + 4], arrM256dNum0[i32Index + 4]);
							arrM256dNum2[i32Index + 4] = _mm256_add_pd(arrM256dNum1[i32Index + 4], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 4], arrM256dNum1[i32Index + 4], 1));
							arrM256dNum1[i32Index + 5] = _mm256_hadd_pd(arrM256dNum0[i32Index + 5], arrM256dNum0[i32Index + 5]);
							arrM256dNum2[i32Index + 5] = _mm256_add_pd(arrM256dNum1[i32Index + 5], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 5], arrM256dNum1[i32Index + 5], 1));
							arrM256dNum1[i32Index + 6] = _mm256_hadd_pd(arrM256dNum0[i32Index + 6], arrM256dNum0[i32Index + 6]);
							arrM256dNum2[i32Index + 6] = _mm256_add_pd(arrM256dNum1[i32Index + 6], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 6], arrM256dNum1[i32Index + 6], 1));
							arrM256dNum1[i32Index + 7] = _mm256_hadd_pd(arrM256dNum0[i32Index + 7], arrM256dNum0[i32Index + 7]);
							arrM256dNum2[i32Index + 7] = _mm256_add_pd(arrM256dNum1[i32Index + 7], _mm256_permute2f128_pd(arrM256dNum1[i32Index + 7], arrM256dNum1[i32Index + 7], 1));

							arrM256dTemp[0] = _mm256_setr_pd(_mm256_cvtsd_f64(arrM256dNum2[i32Index]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 1]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 2]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 3]));
							arrM256dTemp[1] = _mm256_setr_pd(_mm256_cvtsd_f64(arrM256dNum2[i32Index + 4]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 5]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 6]), _mm256_cvtsd_f64(arrM256dNum2[i32Index + 7]));

							memcpy(&arrF64Temp[i32Index], &arrM256dTemp, sizeof(double) * 8);
						}

						if(m_i32Column % 4 > 0)
						{
							for(int32_t i32Index = (m_i32Column / 4) * 4; i32Index < m_i32Column; i32Index++)
							{
								double f64Temp = m_pF64Buffer[i32Row * m_i32Column + i32Index];

								arrF64Temp[0] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column];
								arrF64Temp[1] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 1];
								arrF64Temp[2] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 2];
								arrF64Temp[3] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 3];

								arrF64Temp[4] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 4];
								arrF64Temp[5] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 5];
								arrF64Temp[6] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 6];
								arrF64Temp[7] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 7];
							}
							
							for(int32_t i32Index = (m_i32Column / 4) * 4; i32Index < m_i32Column; i32Index++)
							{
								double f64Temp = m_pF64Buffer[i32Row * m_i32Column + i32Index];

								arrF64Temp[8] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 8];
								arrF64Temp[9] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 9];
								arrF64Temp[10] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 10];
								arrF64Temp[11] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 11];

								arrF64Temp[12] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 12];
								arrF64Temp[13] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 13];
								arrF64Temp[14] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 14];
								arrF64Temp[15] += f64Temp * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column + 15];
							}
						}

						memcpy(&pMatResult->m_pF64Buffer[i32Row * matOperand.m_i32Column + i32Column], arrF64Temp, sizeof(double) * 16);
					}
				}
			}
		}

		if(matOperand.m_i32Column % 16 > 0)
		{
			for(int32_t i32Row = 0; i32Row < m_i32Row; i32Row++)
			{
				for(int32_t i32Column = (matOperand.m_i32Column / 16) * 16; i32Column < matOperand.m_i32Column; i32Column++)
				{
					arrM256dNum0[0] = _mm256_setzero_pd();

					for(int32_t i32Index = 0; i32Index < m_i32Column / 4; i32Index++)
					{
						arrM256dMul[0] = _mm256_mul_pd(pM256dMatrix1[i32Row * (m_i32Column / 4) + i32Index], pM256dMatrix2[i32Column * (matOperand.m_i32Row / 4) + i32Index]);

						arrM256dNum0[0] = _mm256_add_pd(arrM256dNum0[0], arrM256dMul[0]);
					}

					arrM256dNum1[0] = _mm256_hadd_pd(arrM256dNum0[0], arrM256dNum0[0]);
					arrM128dNum2[0] = _mm_add_pd(_mm256_extractf128_pd(arrM256dNum1[0], 0), _mm256_extractf128_pd(arrM256dNum1[0], 1));

					arrF64Temp[0] = _mm_cvtsd_f64(arrM128dNum2[0]);

					if(m_i32Column % 4 > 0)
					{
						for(int32_t i32Index = (m_i32Column / 4) * 4; i32Index < m_i32Column; i32Index++)
							arrF64Temp[0] += m_pF64Buffer[i32Row * m_i32Column + i32Index] * matOperand.GetBuffer()[i32Index * matOperand.m_i32Column + i32Column];
					}

					memcpy(&pMatResult->m_pF64Buffer[i32Row * matOperand.m_i32Column + i32Column], arrF64Temp, sizeof(double));
				}
			}
		}

		free(pM256dMatrix1);
		free(pM256dMatrix2);

		bMul = true;
	}
	while(false);

	return bMul;
}
