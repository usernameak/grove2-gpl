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

package org.aerisdev.bindingtool.desc;

import com.google.common.base.Strings;
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class BindingDescriptor extends NamespaceDescriptor {
    private final List<IncludeDescriptor> includes = new ArrayList<>();
    private String dll;
    private String module;
    private boolean needsModuleLoader = false;

    public String getDll() {
        return dll;
    }

    public void setDll(String dll) {
        this.dll = dll;
    }

    public String getModule() {
        return module;
    }

    public boolean getNeedsModuleLoader() {
        return needsModuleLoader;
    }

    public BindingDescriptor() {
        super(null);
    }

    public void parseFromFile(String filename) throws ParserConfigurationException, IOException, SAXException, DescriptorParseException {
        File xmlFile = new File(filename);

        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setNamespaceAware(true);
        DocumentBuilder dBuilder = factory.newDocumentBuilder();
        Document doc = dBuilder.parse(xmlFile);

        Element root = doc.getDocumentElement();

        parseFromXML(root);
    }

    public BaseDescriptor lookupType(FullyQualifiedName fqn) {
        if (fqn == null) return null;

        BaseDescriptor d = this;
        for (String name : fqn.getQualifiers()) {
            d = d.querySubdescriptor(name);
            if (d == null) return null;
        }
        return d;
    }

    @Override
    public void parseFromXML(Element root) throws DescriptorParseException {
        final String BINDINGS_TAG_NAME = "bindings";

        if (!BINDINGS_TAG_NAME.equals(root.getTagName()) || !BaseDescriptor.NAMESPACE_URI.equals(root.getNamespaceURI())) {
            throw new DescriptorParseException("Descriptor root element invalid");
        }

        super.parseFromXML(root);

        dll = Strings.emptyToNull(root.getAttribute("dll"));
        if (dll == null) throw new DescriptorParseException("Binding descriptor missing dll name");

        module = Strings.emptyToNull(root.getAttribute("module"));

        if ("true".equals(root.getAttribute("needsmoduleloader"))) {
            needsModuleLoader = true;
        }
    }

    @SuppressWarnings("SwitchStatementWithTooFewBranches")
    @Override
    protected BaseDescriptor resolveTypeName(String name) throws DescriptorParseException {
        return switch (name) {
            case "include" -> new IncludeDescriptor(this);
            default -> super.resolveTypeName(name);
        };
    }

    public List<IncludeDescriptor> getIncludes() {
        return includes;
    }

    @Override
    protected void handleIncludeDescriptor(IncludeDescriptor desc) throws DescriptorParseException {
        super.handleIncludeDescriptor(desc);

        includes.add(desc);
    }

    @Override
    public boolean isNamed() {
        return false;
    }

    @Override
    public void merge(BaseDescriptor from) {
        super.merge(from);

        includes.addAll(((BindingDescriptor) from).includes);
    }

    @Override
    public String mangleName() {
        return "grBinding_";
    }
}
