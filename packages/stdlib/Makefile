ROOT := $(abspath ../..)
PACKAGES := b64 config crypto db error fmt fs gcsv gsql http httplib io json math net nn os random s256 sqlite std strings tar tensor time ui urllib xzip

.PHONY: build

sync:
	cp "$(ROOT)/lib/b64.gjs" b64/__self__.gjs
	cp "$(ROOT)/lib/config.gjs" config/__self__.gjs
	cp "$(ROOT)/lib/crypto.gjs" crypto/__self__.gjs
	cp "$(ROOT)/lib/db/__self__.gjs" db/__self__.gjs
	cp "$(ROOT)/lib/db/sqlite.gjs" db/sqlite.gjs
	cp "$(ROOT)/lib/std/error.gjs" error/__self__.gjs
	cp "$(ROOT)/lib/fmt/color.gjs" fmt/color.gjs
	cp "$(ROOT)/lib/fmt/fms.gjs" fmt/fms.gjs
	cp "$(ROOT)/lib/fs.gjs" fs/__self__.gjs
	cp "$(ROOT)/lib/gcsv.gjs" gcsv/__self__.gjs
	cp "$(ROOT)/lib/gsql.gjs" gsql/__self__.gjs
	cp "$(ROOT)/lib/gsql/db.gjs" gsql/db.gjs
	cp "$(ROOT)/lib/http.gjs" http/__self__.gjs
	cp "$(ROOT)/lib/httplib/__self__.gjs" httplib/__self__.gjs
	cp "$(ROOT)/lib/httplib/http.gjs" httplib/http.gjs
	cp "$(ROOT)/lib/httplib/src/get.gjs" httplib/src/get.gjs
	cp "$(ROOT)/lib/httplib/src/post.gjs" httplib/src/post.gjs
	cp "$(ROOT)/lib/io.gjs" io/__self__.gjs
	cp "$(ROOT)/lib/json.gjs" json/__self__.gjs
	cp "$(ROOT)/lib/math.gjs" math/__self__.gjs
	cp "$(ROOT)/lib/net/__self__.gjs" net/__self__.gjs
	cp "$(ROOT)/lib/net/proxy.gjs" net/proxy.gjs
	cp "$(ROOT)/lib/net/socket.gjs" net/socket.gjs
	cp "$(ROOT)/lib/net/websocket.gjs" net/websocket.gjs
	cp "$(ROOT)/lib/nn.gjs" nn/__self__.gjs
	cp "$(ROOT)/lib/os.gjs" os/__self__.gjs
	cp "$(ROOT)/lib/os/env.gjs" os/env.gjs
	cp "$(ROOT)/lib/os/exec.gjs" os/exec.gjs
	cp "$(ROOT)/lib/os/fruit.gjs" os/fruit.gjs
	cp "$(ROOT)/lib/os/proc.gjs" os/proc.gjs
	cp "$(ROOT)/lib/os/sys.gjs" os/sys.gjs
	cp "$(ROOT)/lib/os/user.gjs" os/user.gjs
	cp "$(ROOT)/lib/os/which.gjs" os/which.gjs
	cp "$(ROOT)/lib/random.gjs" random/__self__.gjs
	cp "$(ROOT)/lib/s256/__self__.gjs" s256/__self__.gjs
	cp "$(ROOT)/lib/s256/sha.gjs" s256/sha.gjs
	cp "$(ROOT)/lib/sqlite/db.gjs" sqlite/__self__.gjs
	cp "$(ROOT)/lib/sqlite/db.gjs" sqlite/db.gjs
	cp "$(ROOT)/lib/std/array.gjs" std/array.gjs
	cp "$(ROOT)/lib/std/error.gjs" std/error.gjs
	cp "$(ROOT)/lib/std/helper.gjs" std/helper.gjs
	cp "$(ROOT)/lib/std/str.gjs" std/str.gjs
	cp "$(ROOT)/lib/strings/strings.gjs" strings/strings.gjs
	cp "$(ROOT)/lib/strings/strings.gjs" strings/__self__.gjs
	cp "$(ROOT)/lib/tar.gjs" tar/__self__.gjs
	cp "$(ROOT)/lib/tensor.gjs" tensor/__self__.gjs
	cp "$(ROOT)/lib/time.gjs" time/__self__.gjs
	cp "$(ROOT)/lib/ui.gjs" ui/__self__.gjs
	cp "$(ROOT)/lib/urllib/request.gjs" urllib/request.gjs
	cp "$(ROOT)/lib/urllib/server.gjs" urllib/server.gjs
	cp "$(ROOT)/lib/xzip.gjs" xzip/__self__.gjs

build: sync
	@set -e; \
	for package in $(PACKAGES); do \
		mkdir -p "$$package/modules"; \
		cp "$(ROOT)/lib/__builtin__.gjs" "$$package/modules/__builtin__.gjs"; \
		printf 'Building standard package %s\n' "$$package"; \
		(cd "$$package" && PATH="$(ROOT):$$PATH" "$(ROOT)/golem" build); \
		rm -f "$$package/modules/__builtin__.gjs"; \
		rmdir "$$package/modules" 2>/dev/null || true; \
	done; \
	mkdir -p "$(ROOT)/lib/openv/modules"; \
	cp "$(ROOT)/lib/__builtin__.gjs" "$(ROOT)/lib/openv/modules/__builtin__.gjs"; \
	printf 'Building add-on package openv\n'; \
	(cd "$(ROOT)/lib/openv" && PATH="$(ROOT):$$PATH" "$(ROOT)/golem" build); \
	rm -f "$(ROOT)/lib/openv/modules/__builtin__.gjs"; \
	rmdir "$(ROOT)/lib/openv/modules" 2>/dev/null || true
