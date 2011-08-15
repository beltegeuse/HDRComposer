import sys
import os
import subprocess
import time
import argparse
import ConfigParser

headers = []

#########################
# Configuration 
#########################
class AbstractConfig:
    def __init__(self):
        self.makefiletype = ""
        self.makecommand = ""
    
    def GenerateCMakeConfigCommand(self, build_type):
        return 'cmake -E chdir Build/ cmake -DCMAKE_BUILD_TYPE=' + build_type + ' ' + '-G "' + self.makefiletype + '" -DCMAKE_INSTALL_PREFIX=Build/ ..'
    
    def CompileCommand(self):
        return self.makecommand + " -f Makefile"
    
    def Save(self, build_type):
        file = open('Build/ConfigPythonScript.cfg', 'r')
        cfg = ConfigParser.ConfigParser()
        cfg.add_section('Generator')
        cfg.set("Generator", "makecommand ", self.makecommand)
        cfg.set("Generator", "makefiletype ", self.makefiletype)
        cfg.set("Generator", "buildtype ", build_type)
        cfg.write(file)

    def Load(self):
        cfg = ConfigParser.ConfigParser()
        self.makefiletype = cfg.get('Generator', "makecommand ")
        self.makefiletype = cfg.get('Generator', "makefiletype ")
        
class MinGW32Config(AbstractConfig):
    def __init__(self):
        AbstractConfig.__init__(self)
        self.makecommand = "mingw32-make"
        self.makefiletype = "MinGW Makefiles"

class LinuxConfig(AbstractConfig):
    def __init__(self):
        AbstractConfig.__init__(self)
        self.makecommand = "make"
        self.makefiletype = "Unix Makefiles"


###########################
# Exec class
###########################
class Compilation:
    configs = {"mingw" : MinGW32Config, "linux" : LinuxConfig}
    
    def __init__(self):
        self.__platform = sys.platform
        self.__path = "Build/"
        self.InitialiseRootDirectory()

    # Pour bien se positionner
    def InitialiseRootDirectory(self):
        print("[INFO] Positionnement dans le repertoire.")
        path = os.path.abspath(os.path.curdir)
        path = path.split(os.path.sep)
        if(path[-1] == "scripts"):
            print("[INFO] Cd ..")
            os.chdir("..")

    # Initilisation de l'environement.
    def Initialisation(self, generator, type):
        print("[INFO] Initialisation ...")
        if(not Compilation.configs.has_key(generator.lower())):
            print("[ERREUR] Generator :" + generator + " is unknow !")
            return
        # Pour verifier que les flags soient Bon
        if(type != "debug" and type != "release"):
            print("[ERREUR] Flags : " + type)
            print("[INFO] You have to choose beetween release/debug")
            return

        if(not os.path.exists("Build")): 
            print("[INFO] Mkdir Build.")
            os.mkdir("Build")
        
        generatorInstance = Compilation.configs[generator.lower()]()
        print "[EXEC] " + generatorInstance.GenerateCMakeConfigCommand(type)
        os.system(generatorInstance.GenerateCMakeConfigCommand(type))

        generatorInstance.Save(type)
        
    def CompilerAll(self, args):
        self.Compiler(args)
        
        for el in headers:
            print("")
            print("======================== ")
            print("======== " + el + " ========= ")
            print("======================== ")
            print("")
            sys.stdout.flush()
            self.Compiler([el])

    def Compiler(self,args):
        #
        # Get command
        #
        commande = ""
        config = AbstractConfig()
        config.Load()
        commande += config.CompileCommand()
        
        # Add compilation flags
        for arg in args:
            commande += " " + arg

        self.__searchBuildDirAndExecute(commande)
        

    def __searchBuildDirAndExecute(self, commande):
        if(os.access("Build", os.R_OK)):
            os.chdir("Build")
            os.system(commande)
        elif(os.access("..//Build", os.R_OK)):
            os.chdir("..//Build")
            os.system(commande)
        else:
            print("[ERROR] No Build Directory")

if __name__=="__main__":
    # Create Arg list
    parser = argparse.ArgumentParser(description='Python CMAKE Utils.')
    parser.add_argument('--init', action="store", dest="generator")
    parser.add_argument('--type', action="store", dest="type", default="release")
    parser.add_argument('--compile', action='append', dest='optFlags', default=[], help='Add Compilation Flags or options')
    parser.add_argument('-j', action="store", dest="jobs", default="1")
    parser.add_argument('--version', action='version', version='%(prog)s 0.3')
    # Get result
    results = parser.parse_args()
    
    #
    # Check if there is no options
    #
    if((results.generator == None) & (len(results.optFlags) == 0)):
        parser.error("Need to specify action")
    
    #
    # Print options
    #
    print ' ==== Options ===='
    print 'generator        =', results.generator
    print 'type             =', results.type
    print 'build flags      =', results.optFlags
    print ''
    #
    # Process options
    #
    c = Compilation()
    if(results.generator):
        c.Initialisation(results.generator, results.type)
    if(len(results.optFlags) != 0):
        results.optFlags.append("-j"+results.jobs)
        c.CompilerAll(results.optFlags)
