pipeline {
    agent any
    stages {
        stage('Checkout Pollenflug') {
            steps {
                git branch: 'master',
                        url: 'https://github.com/andywuest/harbour-pollenflug.git'
            }
        }
        stage('Run C++ tests') {
            steps {
                sh "cd tests && ls -l && bash runTests.sh"
            }
        }
    }
    post {
        always {
            xunit(
                    thresholds: [skipped(failureThreshold: '0'), failed(failureThreshold: '0')],
                    tools: [QtTest(pattern: '**/*results.xml'), ]
            )
        }
    }
}

