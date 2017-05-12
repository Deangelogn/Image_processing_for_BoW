cmake_minimum_required(VERSION 3.7)
project(MO815_BoW)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c header/image.h src/image.c src/histogram.c header/histogram.h header/adjRelation.h src/adjRelation.c header/morphology.h src/morphology.c header/myMath.h src/myMath.c header/alg.h src/alg.c header/bow.h src/bow.c header/stringManipulation.h src/stringManipulation.c header/direct.h src/direct.c src/label.c header/label.h header/ImagePile.h src/ImagePile.c)
add_executable(Clion ${SOURCE_FILES})