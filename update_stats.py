import os
import re

def count_difficulties():
    easy, medium, hard = 0, 0, 0
    for root, dirs, files in os.walk("."):
        # Ignore hidden folders like .git and .github
        if ".github" in root or ".git" in root:
            continue
        if "README.md" in files and root != ".":
            readme_path = os.path.join(root, "README.md")
            try:
                with open(readme_path, "r", encoding="utf-8") as f:
                    content = f.read()
                    if re.search(r"\bEasy\b", content, re.IGNORECASE):
                        easy += 1
                    elif re.search(r"\bMedium\b", content, re.IGNORECASE):
                        medium += 1
                    elif re.search(r"\bHard\b", content, re.IGNORECASE):
                        hard += 1
            except Exception:
                pass
    return easy, medium, hard

def update_readme(easy, medium, hard):
    total = easy + medium + hard
    stats_markdown = f"""### 📊 LeetCode Progress Dashboard

| Difficulty | Solved Count |
| :--- | :--- |
| 🟢 **Easy** | {easy} |
| 🟡 **Medium** | {medium} |
| 🔴 **Hard** | {hard} |
| 🔢 **Total** | **{total}** |

_Last Updated automatically via GitHub Actions_
"""

    readme_path = "README.md"
    
    # Read the existing content safely
    if os.path.exists(readme_path):
        with open(readme_path, "r", encoding="utf-8") as f:
            readme_content = f.read()
    else:
        readme_content = ""

    # Replace ONLY the stats section block
    pattern = r".*?"
    if re.search(pattern, readme_content, re.DOTALL):
        new_content = re.sub(pattern, stats_markdown, readme_content, flags=re.DOTALL)
    else:
        # If the block isn't found, just append it neatly
        new_content = readme_content.strip() + "\n\n" + stats_markdown

    # Write back using standard Linux line breaks to stop Git from tripping over CRLF
    with open(readme_path, "w", encoding="utf-8", newline="\n") as f:
        f.write(new_content)

if __name__ == "__main__":
    e, m, h = count_difficulties()
    update_readme(e, m, h)