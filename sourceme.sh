# shellcheck shell=sh
ab_build() {
	clang++ main.cc -o main -lallegro -lallegro_primitives
}
