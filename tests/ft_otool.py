#! /usr/bin/env python3

import subprocess
from subprocess import Popen, PIPE
import os
from unittest import TestCase
import unittest as ut

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

dir_path = os.path.dirname(os.path.realpath(__file__))
nm_path = os.path.join(dir_path, "../ft_otool")

class Base(TestCase):
	def compare(self, test_files):
		for f in test_files:
			out1 = subprocess.check_output([nm_path, os.path.join(self.test_path, f)])
			out2 = subprocess.check_output(["otool", "-t", os.path.join(self.test_path, f)])
			self.assertEqual(out1, out2)

	def compare_multiple(self, test_files, nb):
		for f in test_files:
			fs = [os.path.join(self.test_path, f) for i in range(nb)]
			out1 = subprocess.check_output([nm_path] + fs)
			out2 = subprocess.check_output(["otool", "-t"] + fs)
			self.assertEqual(out1, out2)

class Easy(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests")

	def test_easy(self):
		self.compare(["test_facile", "test_moins_facile"])
	
	def test_multiple(self):
		self.compare_multiple(["test_facile", "test_moins_facile"], 2)
		self.compare_multiple(["test_facile", "test_moins_facile"], 3)
		self.compare_multiple(["test_facile", "test_moins_facile"], 4)

class M32(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/32")
		self.files = os.listdir(self.test_path)

	def test_32(self):
		self.compare(self.files)

class M64(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/64")
		self.files = os.listdir(self.test_path)

	def test_64(self):
		self.compare(self.files)

class Fat(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/fat")
		self.files = os.listdir(self.test_path)
	
	def test_fat(self):
		self.compare(self.files)

class LibStat(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/lib_stat")
		self.files = os.listdir(self.test_path)
	
	def test_lib_stat(self):
		self.compare(self.files)

class FatLib(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/fat_lib")
		self.files = os.listdir(self.test_path)

	def test_fat_lib(self):
		# self.compare(["PN548_API.dylib", "PN548_HAL_OSX.dylib", "PN548_OSX.dylib", "libAccountPolicyTranslation.dylib", "libFosl_dynamic.dylib", "libarchive.dylib"])
		# self.compare(["libate.dylib", "libblas.dylib", "libc++.1.dylib", "libc++.dylib", "libcblas.dylib", "libclapack.dylib"])
		# self.compare(["libcom_err.dylib", "libcompression.dylib", "libcoretls.dylib", "libdes425.dylib", "libdns_services.dylib", "libextension.dylib"])
		self.compare(self.files)

class MoreDylib(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/dylib")
		self.files = os.listdir(self.test_path)

	def test_more_dylib(self):
		self.compare(self.files)

# class Corrupted(Base):
# 	def setUp(self):
# 		self.test_path = os.path.join(dir_path, "custom_tests/corrupt")
# 		self.files = ["bad_string_index"]
	
# 	def test_corrupted(self):
# 		self.compare(self.files)

if __name__ == '__main__':
	ut.main()