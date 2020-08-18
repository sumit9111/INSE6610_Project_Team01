from java.util import Date
from java.text import SimpleDateFormat
from org.sleuthkit.autopsy.casemodule import Case
from org.sleuthkit.autopsy.report import GeneralReportModuleAdapter
from org.sleuthkit.datamodel import TskData

class ForensicLucidReportModule(GeneralReportModuleAdapter):
    def getName(self):
        return "Forensic Lucid 6610 Report"
    def getDescription(self):
        return "Generate list of all .jpg files from two days before the date of incident (date of incident is 17 may 2018) and encode output to Forensic Lucid observation format "
    def getRelativeFilePath(self):
        return "ForensicLucidReport.txt"
    def generateReport(self, baseReportDir, progressBar):
    
            progressBar.setIndeterminate(False)
            progressBar.start()
     
            autopsyCase = Case.getCurrentCase()
            sleuthkitCase = autopsyCase.getSleuthkitCase()
            
            #calculate miliseconds of specific date before incident 
            sdf = SimpleDateFormat("dd-M-yyyy hh:mm:ss")
            date2018=sdf.parse("15-05-2018 00:00:00")
            crtime2018=date2018.getTime()/ 1000


            report = open(baseReportDir + '\\' + self.getRelativeFilePath(), 'w')
            
            #find all jpg file type
            allfiles = sleuthkitCase.findAllFilesWhere("NOT meta_type = " +str(TskData.TSK_FS_META_TYPE_ENUM.TSK_FS_META_TYPE_DIR.getValue()))
            
            progressBar.setMaximumProgress(allfiles.size())
            report.write( "Autopsy_FronsicLucid_6610\n") 
            report.write( "where\n")
            report.write( "observation sequence jpg_files =\n{\n")
            index=1
            #write forensic lucid format of observations
            for tmpfile in allfiles:
                if tmpfile.getNameExtension()=="jpg" and tmpfile.getCrtime()>crtime2018:
                    if index!=1:
                        report.write(",") 
                    report.write("file_o_"+str(index)+"\n") 
                    index+=1
                    
            report.write("};\n")
            index=1
            for tmpfile in allfiles:
                   if tmpfile.getNameExtension()=="jpg" and tmpfile.getCrtime()>crtime2018:
                        md5 = tmpfile.getMd5Hash()
                        if md5 is None:
                            md5 = ""
                        report.write("observation file_o_"+str(index)+"=(\n[Filename:\""+ tmpfile.getName()+"\",\nDateTime:\""+tmpfile.getCrtimeAsDate()+"\",\nLastAccessed:\""+tmpfile.getAtimeAsDate()+"\",\nPath:\""+tmpfile.getParentPath()+"\",\nMD5Hash:\""+md5+"\"],\n1,0,1.0\n);\n") 	
                        index+=1
                   progressBar.increment()
                   
            report.write("end")
            
            
            Case.getCurrentCase().addReport(report.name, "ForensicLucidReport.txt", "Forensic Lucid Report");
            report.close()
            progressBar.complete()