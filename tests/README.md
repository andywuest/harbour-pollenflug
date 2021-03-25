## Add "Custom Process Step
# testdata dir has to exists -> mkdir als ersten custom process step

Command:           cp
Arguments:         %{buildDir}/../tests/testdata/*.json %{buildDir}/testdata
Working directory: %{buildDir}

