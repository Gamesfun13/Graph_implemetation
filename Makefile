CC = gcc
CFLAGS = -Wall
TARGET = graph_dfs
SRC = main.c stack_functions.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Run a single test case: extract the cost from output and compare to expected
# Usage: $(call run_test, src, dst, expected_cost)
define run_test
	@result=$$(./$(TARGET) $(1) $(2) 2>&1 | grep "Cost:" | awk '{print $$2}'); \
	if [ "$$result" = "$(3)" ]; then \
		echo "PASS: $(TARGET) $(1) $(2) -> cost $$result"; \
	else \
		echo "FAIL: $(TARGET) $(1) $(2) -> expected $(3), got $$result"; \
		exit 1; \
	fi
endef

test: $(TARGET)
	@echo "Running tests..."
	$(call run_test,0,3,13)
	$(call run_test,1,4,14)
	$(call run_test,1,5,6)
	$(call run_test,2,3,9)
	$(call run_test,2,9,10)
	$(call run_test,3,0,13)
	$(call run_test,3,8,9)
	$(call run_test,4,1,14)
	$(call run_test,4,6,8)
	$(call run_test,5,1,6)
	$(call run_test,5,2,7)
	$(call run_test,5,6,12)
	$(call run_test,6,4,8)
	$(call run_test,6,7,15)
	$(call run_test,7,6,15)
	$(call run_test,8,5,11)
	$(call run_test,9,8,23)
	@echo "All tests passed!"

# Test multi-hop paths
test_paths: $(TARGET)
	@echo "Running multi-hop path tests..."
	$(call run_test,4,8,60)
	$(call run_test,9,2,41)
	$(call run_test,0,8,22)
	$(call run_test,2,7,71)
	@echo "All multi-hop path tests passed!"

clean:
	rm -f $(TARGET)