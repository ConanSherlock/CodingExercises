env.BUILD_MACHINE = "winagent01"
env.WORK_SPACE = "C:/Jenkins/workspace/CodingExercises"
env.SUCCESS = 0
env.BUILD_ERROR_STRING = "Error in build step"
env.TEST_ERROR_STRING = "Error in running tests"
env.DEPLOY_ERROR_STRING = "Error in deployment"

def BRANCH_NAME = "${env.JOB_NAME.substring(env.JOB_NAME.lastIndexOf('/') + 1, env.JOB_NAME.length())}"

pipeline {
    agent {
        node {
            label env.BUILD_MACHINE
            customWorkspace env.WORK_SPACE
        }
    }

    stages {
        stage('Set up Environment') {
            steps {
                script {
                    jenkins_functions = load "jenkins_functions.groovy"
                }
                dir('test/tools/conda') {
                    bat 'conda env update -q --file conda_environment.yml'
                    bat 'call conda activate cs_aoc'
                }
            }
        }

        stage('Build') {
            steps {
                echo 'Building..'
				dir('test/tools/automation') {
                    script {
                        def result = jenkins_functions.runCondaWin("python aoc_build.py --configFile ../script_configs/aoc_build_all.yaml")
                        if(result != env.SUCCESS) {
                            currentBuild.result = 'FAIL'
                            result = "FAIL"
                            error(env.BUILD_ERROR_STRING)
                        }
                    }
                }
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
				dir('test/tools/automation') {
                    script {
                        def result = jenkins_functions.runCondaWin("python aoc_run_unit_tests.py --configFile ../script_configs/aoc_run_2015_unit_tests.yaml")
                        if(result != env.SUCCESS) {
                            currentBuild.result = 'FAIL'
                            result = "FAIL"
                            error(env.TEST_ERROR_STRING)
                        }
                    }
                }
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
    post
    {
        failure
        {
            mail bcc: '',
                  cc: '',
                  charset: 'UTF-8',
                  mimeType: 'text/html',
                  replyTo: '',
                  subject: "AoC Jenkins FAILURE: -> ${env.JOB_NAME}",
                  to: "${env.DEFAULT_MAIL_RECIPIENTS}",
                  from: "Jenkins",
                  body: "<b>Jenkins Pipeline has failed</b><br>\n\n<br>Project: ${env.JOB_NAME} <br>Build Number: ${env.BUILD_NUMBER} <br>Build URL: ${env.BUILD_URL}<br>";
        }

        success
        {
            mail bcc: '',
                  cc: '',
                  charset: 'UTF-8',
                  mimeType: 'text/html',
                  replyTo: '',
                  subject: "AoC Jenkins SUCCESS: -> ${env.JOB_NAME}",
                  to: "${env.DEFAULT_MAIL_RECIPIENTS}",
                  from: "Jenkins",
                  body: "<b>Jenkins Pipeline has succeeded</b><br>\n\n<br>Project: ${env.JOB_NAME} <br>Build Number: ${env.BUILD_NUMBER} <br>Build URL: ${env.BUILD_URL}<br>";
        }
    }
}
