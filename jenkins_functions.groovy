def runCondaWin(command) {
    def processCheck = """${bat(returnStatus: true,
   script: '''
               call conda activate cs_aoc
               call ''' + command + '''
           '''
   )}"""

    return processCheck
}

return this