TEST_DIR="tests"

coverage-html:
	@cd $(TEST_DIR) && go test -coverprofile=coverage.out -coverpkg=../... -timeout 30s -run ^Test dlist_test.go queue_test.go
	@go tool cover -html=$(TEST_DIR)/coverage.out -o $(TEST_DIR)/coverage.html
	@rm $(TEST_DIR)/coverage.out