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
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}