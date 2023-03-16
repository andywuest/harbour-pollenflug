## Add "Custom Process Step"

Note: testdata dir has to exist -> mkdir as first custom process step

- **Command**:           cp
- **Arguments**:         %{buildDir}/../cpp/testdata/*.json %{buildDir}/testdata
- **Working directory**: %{buildDir}
