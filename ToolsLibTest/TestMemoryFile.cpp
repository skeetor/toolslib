#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS

#include "gtest/gtest.h"

#include "toolslib/files/MemoryFile.h"

using namespace std;
using namespace toolslib;
using namespace toolslib::files;

namespace
{
	class TMemoryFile
	: public ::testing::Test
	{
	public:
		TMemoryFile() {}

		MemoryFile m_file;
	};

	TEST_F(TMemoryFile, BasicTests)
	{
		string file = "dummy.txt";

		m_file.setFilename(file);

		EXPECT_EQ(file, (string)m_file.getFilename());
		EXPECT_FALSE(m_file.isOpen());
		EXPECT_TRUE(m_file.isEOF());
		EXPECT_EQ(invalid64_t, m_file.tell());
		EXPECT_EQ(invalid64_t, m_file.length());

		EXPECT_TRUE(m_file.open());
		EXPECT_TRUE(m_file.isOpen());
		EXPECT_EQ(0, m_file.length());
		m_file.resize(20);
		EXPECT_EQ(20, m_file.length());
	}

	TEST_F(TMemoryFile, SeekEmptyFile)
	{
		EXPECT_EQ(invalid64_t, m_file.seek(0, IFile::cur));
		EXPECT_EQ(invalid64_t, m_file.seek(0, IFile::set));
		EXPECT_EQ(invalid64_t, m_file.seek(0, IFile::end));

		EXPECT_TRUE(m_file.open());

		EXPECT_EQ(0, m_file.seek(0, IFile::cur));
		EXPECT_EQ(0, m_file.seek(0, IFile::set));
		EXPECT_EQ(0, m_file.seek(0, IFile::end));

		m_file.close();
		EXPECT_EQ(invalid64_t, m_file.seek(0, IFile::cur));
		EXPECT_EQ(invalid64_t, m_file.seek(0, IFile::set));
		EXPECT_EQ(invalid64_t, m_file.seek(0, IFile::end));
	}

	TEST_F(TMemoryFile, ReadEmptyFile)
	{
		char buffer[32] = { 0 };
		char cmp[32] = { 0 };

		EXPECT_EQ(invalid64_t, m_file.read(buffer, 0));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));

		EXPECT_EQ(invalid64_t, m_file.read(buffer, 10));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));

		EXPECT_TRUE(m_file.open());

		EXPECT_EQ(0, m_file.read(buffer, 0));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));
		EXPECT_EQ(0, m_file.read(buffer, 10));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));

		m_file.close();
		EXPECT_EQ(invalid64_t, m_file.read(buffer, 0));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));
		EXPECT_EQ(invalid64_t, m_file.read(buffer, 10));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));
	}

	TEST_F(TMemoryFile, OpenMode)
	{
		char buffer[32] = { 0 };
		char cmp[32] = { 0 };

		// Read only as default
		EXPECT_TRUE(m_file.open());
		EXPECT_EQ(0, m_file.length());
		EXPECT_EQ(invalid64_t, m_file.write(cmp, sizeof(cmp)));
		EXPECT_EQ(0, m_file.length());
		m_file.close();

		memset(cmp, 0xda, sizeof(cmp));
		IFile::open_mode md = { true,	true,	true,	false,	false,   false };
		EXPECT_TRUE(m_file.open(md));
		EXPECT_EQ(0, m_file.length());
		EXPECT_EQ((int64_t)sizeof(cmp), m_file.write(cmp, sizeof(cmp)));
		EXPECT_EQ((int64_t)sizeof(cmp), m_file.length());
		EXPECT_EQ(0, m_file.seek(0, IFile::set));
		EXPECT_EQ((int64_t)sizeof(buffer), m_file.read(buffer, sizeof(buffer)));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));
		m_file.close();

		// reopen the file.
		memset(buffer, 0, sizeof(buffer));
		md = { true,	true,	true,	false,	false,   false };
		EXPECT_TRUE(m_file.open(md));
		EXPECT_EQ((int64_t)sizeof(buffer), m_file.length());
		EXPECT_EQ((int64_t)sizeof(buffer), m_file.read(buffer, sizeof(buffer)));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));
		m_file.close();

		md = { true,	true,	true,	false,	false,   true };
		EXPECT_TRUE(m_file.open(md));
		EXPECT_EQ(0, m_file.length());
	}

	TEST_F(TMemoryFile, ReadWriteFile)
	{
		char buffer[32] = { 0 };
		char cmp[32] = { 0 };

		IFile::open_mode md = { true,	true,	true,	false,	false,   true };

		EXPECT_TRUE(m_file.open(md));
		EXPECT_EQ(0, m_file.length());

		memset(cmp, 0xda, sizeof(cmp));
		EXPECT_FALSE(m_file.isEOF());
		EXPECT_EQ((int64_t)sizeof(cmp), m_file.write(cmp, sizeof(cmp)));
		EXPECT_EQ((int64_t)sizeof(cmp), m_file.length());
		EXPECT_FALSE(m_file.isEOF());

		EXPECT_EQ(0, m_file.seek(0, IFile::set));
		EXPECT_EQ((int64_t)sizeof(buffer), m_file.read(buffer, sizeof(buffer)));
		EXPECT_FALSE(m_file.isEOF());

		EXPECT_EQ(0, m_file.read(buffer, sizeof(buffer)));
		EXPECT_TRUE(m_file.isEOF());
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));

		EXPECT_EQ(17, m_file.seek(-15, IFile::cur));
		EXPECT_EQ(19, m_file.seek(2, IFile::cur));
		EXPECT_EQ(13, m_file.read(buffer, sizeof(buffer)));
		EXPECT_EQ(31, m_file.seek(1, IFile::end));
		EXPECT_EQ(1, m_file.read(buffer, sizeof(buffer)));

		int32_t val = 0x1d1d1d1d;
		EXPECT_EQ(14, m_file.seek(14, IFile::set));
		EXPECT_EQ((int64_t)sizeof(val), m_file.write(&val, sizeof(val)));
		*((int32_t *)&cmp[14]) = val;
		EXPECT_EQ(0, m_file.seek(0, IFile::set));
		EXPECT_EQ((int64_t)sizeof(buffer), m_file.read(buffer, sizeof(buffer)));
		EXPECT_EQ(0, memcmp(buffer, cmp, sizeof(buffer)));
		EXPECT_EQ(invalid64_t, m_file.seek(100, IFile::set));
		EXPECT_EQ(invalid64_t, m_file.seek(100, IFile::end));
		EXPECT_EQ(invalid64_t, m_file.seek(100, IFile::cur));
	}
}
