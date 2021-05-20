FROM gcc:10 AS base

FROM base AS build
RUN apt-get update -q \
	&& apt-get install -y ccache cmake ninja-build

RUN --mount=type=bind,target=/src,ro \
	--mount=type=cache,target=/root/.ccache \
	cd /src \
	&& hack/hack gen RelWithDebInfo /build/RelWithDebInfo \
	&& CXXFLAGS=-fsanitize=address hack/hack gen Debug /build/Debug \
	&& hack/hack test /build/RelWithDebInfo /build/Debug

FROM base
COPY --from=build /build/RelWithDebInfo/CsvQuery /usr/local/bin

