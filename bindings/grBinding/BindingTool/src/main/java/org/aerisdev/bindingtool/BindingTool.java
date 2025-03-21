// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

package org.aerisdev.bindingtool;

import org.aerisdev.bindingtool.desc.BindingDescriptor;
import org.aerisdev.bindingtool.gen.cs.CsGenerator;
import org.aerisdev.bindingtool.gen.cxxthunks.CxxThunkGenerator;
import picocli.CommandLine;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.util.concurrent.Callable;

@CommandLine.Command(
        name = "BindingTool",
        mixinStandardHelpOptions = true,
        description = "Generates bindings for the GroveEngine2 classes"
)
public class BindingTool implements Callable<Integer> {
    @CommandLine.Option(
            names = {"-l", "--lookup-descriptor"},
            description = "Lookup descriptor XML file(s)"
    )
    private String[] lookupDescriptorFilenames = new String[0];

    @CommandLine.Option(
            names = {"-x", "--descriptor"},
            description = "Main descriptor XML file",
            required = true
    )
    private String descriptorFilename;

    @CommandLine.Option(
            names = {"-c", "--generate-cxx-thunks"},
            description = "Generates C++ thunks, pass an output filename"
    )
    private String generateCxxThunks;

    @CommandLine.Option(
            names = {"-s", "--generate-cs"},
            description = "Generates C# wrappers, pass an output filename"
    )
    private String generateCs;

    @CommandLine.Option(
            names = {"-1", "--use-single-dll"},
            description = "Uses the single-dll filename"
    )
    private boolean useSingleDll;

    @Override
    public Integer call() throws Exception {
        BindingDescriptor lookupDesc = new BindingDescriptor();

        for (String filename : lookupDescriptorFilenames) {
            BindingDescriptor desc = new BindingDescriptor();
            desc.parseFromFile(filename);
            lookupDesc.merge(desc);
        }

        BindingDescriptor desc = new BindingDescriptor();
        desc.parseFromFile(descriptorFilename);
        if (useSingleDll) {
            desc.setDll("grBindingSingleDLL.dll");
        }
        lookupDesc.merge(desc);

        if (generateCxxThunks != null) {
            CxxThunkGenerator gen = new CxxThunkGenerator(desc, lookupDesc);
            try (FileOutputStream fos = new FileOutputStream(generateCxxThunks);
                 OutputStreamWriter osw = new OutputStreamWriter(fos)) {
                osw.write(gen.generate());
            }
        }

        if (generateCs != null) {
            CsGenerator gen = new CsGenerator(desc, lookupDesc);
            try (FileOutputStream fos = new FileOutputStream(generateCs);
                 OutputStreamWriter osw = new OutputStreamWriter(fos)) {
                osw.write(gen.generate());
            }
        }
        return 0;
    }

    public static void main(String[] args) {
        int exitCode = new CommandLine(new BindingTool()).execute(args);
        System.exit(exitCode);
    }
}
